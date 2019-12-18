#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pst_softc {TYPE_2__* iop; struct i2o_bsa_device* info; TYPE_3__* disk; int /*<<< orphan*/  queue; TYPE_1__* lct; } ;
struct i2o_get_param_reply {scalar_t__ result; } ;
struct i2o_device_identity {char* vendor; char* product; char* description; char* revision; } ;
struct i2o_bsa_device {int capacity; int /*<<< orphan*/  block_size; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {char* d_name; int d_maxsize; int d_unit; int d_mediasize; int d_fwsectors; int d_fwheads; int /*<<< orphan*/  d_sectorsize; struct pst_softc* d_drv1; int /*<<< orphan*/  d_strategy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  local_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_VERSION ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2O_BSA_DEVICE_INFO_GROUP_NO ; 
 int /*<<< orphan*/  I2O_PARAMS_OPERATION_FIELD_GET ; 
 int /*<<< orphan*/  I2O_UTIL_DEVICE_IDENTITY_GROUP_NO ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PSTIOP ; 
 int /*<<< orphan*/  M_PSTRAID ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_FIRST ; 
 int /*<<< orphan*/  bcopy (scalar_t__,struct i2o_bsa_device*,int) ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpack (char*,char*,int) ; 
 int /*<<< orphan*/  contigfree (struct i2o_get_param_reply*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct pst_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 TYPE_3__* disk_alloc () ; 
 int /*<<< orphan*/  disk_create (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct i2o_get_param_reply* iop_get_util_params (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pst_shutdown ; 
 int /*<<< orphan*/  pststrategy ; 
 int /*<<< orphan*/  shutdown_post_sync ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static int
pst_attach(device_t dev)
{
    struct pst_softc *psc = device_get_softc(dev);
    struct i2o_get_param_reply *reply;
    struct i2o_device_identity *ident;
    int lun = device_get_unit(dev);
    int8_t name [32];

    if (!(reply = iop_get_util_params(psc->iop, psc->lct->local_tid,
				      I2O_PARAMS_OPERATION_FIELD_GET,
				      I2O_BSA_DEVICE_INFO_GROUP_NO)))
	return ENODEV;

    if (!(psc->info = (struct i2o_bsa_device *)
	    malloc(sizeof(struct i2o_bsa_device), M_PSTRAID, M_NOWAIT))) {
	contigfree(reply, PAGE_SIZE, M_PSTIOP);
	return ENOMEM;
    }
    bcopy(reply->result, psc->info, sizeof(struct i2o_bsa_device));
    contigfree(reply, PAGE_SIZE, M_PSTIOP);

    if (!(reply = iop_get_util_params(psc->iop, psc->lct->local_tid,
				      I2O_PARAMS_OPERATION_FIELD_GET,
				      I2O_UTIL_DEVICE_IDENTITY_GROUP_NO)))
	return ENODEV;
    ident = (struct i2o_device_identity *)reply->result;
#ifdef PSTDEBUG	   
    printf("pst: vendor=<%.16s> product=<%.16s>\n",
	   ident->vendor, ident->product);
    printf("pst: description=<%.16s> revision=<%.8s>\n",
	   ident->description, ident->revision);
    printf("pst: capacity=%lld blocksize=%d\n",
	   psc->info->capacity, psc->info->block_size);
#endif
    bpack(ident->vendor, ident->vendor, 16);
    bpack(ident->product, ident->product, 16);
    sprintf(name, "%s %s", ident->vendor, ident->product);
    contigfree(reply, PAGE_SIZE, M_PSTIOP);

    bioq_init(&psc->queue);

    psc->disk = disk_alloc();
    psc->disk->d_name = "pst";
    psc->disk->d_strategy = pststrategy;
    psc->disk->d_maxsize = 64 * 1024; /*I2O_SGL_MAX_SEGS * PAGE_SIZE;*/
    psc->disk->d_drv1 = psc;
    psc->disk->d_unit = lun;

    psc->disk->d_sectorsize = psc->info->block_size;
    psc->disk->d_mediasize = psc->info->capacity;
    psc->disk->d_fwsectors = 63;
    psc->disk->d_fwheads = 255;

    disk_create(psc->disk, DISK_VERSION);

    printf("pst%d: %lluMB <%.40s> [%lld/%d/%d] on %.16s\n", lun,
	   (unsigned long long)psc->info->capacity / (1024 * 1024),
	   name, psc->info->capacity/(512*255*63), 255, 63,
	   device_get_nameunit(psc->iop->dev));

    EVENTHANDLER_REGISTER(shutdown_post_sync, pst_shutdown,
			  dev, SHUTDOWN_PRI_FIRST);
    return 0;
}