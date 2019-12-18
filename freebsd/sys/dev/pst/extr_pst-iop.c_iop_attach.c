#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iop_softc {int ism; TYPE_1__* reg; int /*<<< orphan*/  handle; int /*<<< orphan*/  r_irq; int /*<<< orphan*/  dev; TYPE_2__* lct; int /*<<< orphan*/ * iop_delayed_attach; } ;
struct i2o_get_param_reply {scalar_t__ result; } ;
struct i2o_device_identity {char* vendor; char* product; char* description; char* revision; } ;
struct TYPE_4__ {scalar_t__ entry_size; int class; int sub_class; int local_tid; int user_tid; int parent_tid; } ;
struct TYPE_3__ {int oqueue_intr_mask; } ;

/* Variables and functions */
#define  I2O_CLASS_DDM 129 
#define  I2O_CLASS_RANDOM_BLOCK_STORAGE 128 
 scalar_t__ I2O_LCT_ENTRYSIZE ; 
 int /*<<< orphan*/  I2O_PARAMS_OPERATION_FIELD_GET ; 
 int I2O_SUBCLASS_ISM ; 
 int I2O_TID_HOST ; 
 int I2O_TID_NONE ; 
 int /*<<< orphan*/  I2O_UTIL_DEVICE_IDENTITY_GROUP_NO ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  M_PSTIOP ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iop_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  contigfree (struct i2o_get_param_reply*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iop_get_lct (struct iop_softc*) ; 
 struct i2o_get_param_reply* iop_get_util_params (struct iop_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iop_intr ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pst_add_raid (struct iop_softc*,TYPE_2__*) ; 

void
iop_attach(void *arg)
{
    struct iop_softc *sc;
    int i;

    sc = arg;
    if (sc->iop_delayed_attach) {
	config_intrhook_disestablish(sc->iop_delayed_attach);
	free(sc->iop_delayed_attach, M_PSTIOP);
	sc->iop_delayed_attach = NULL;
    }

    if (!iop_get_lct(sc)) {
	printf("pstiop: get LCT failed\n");
	return;
    }

    /* figure out what devices are here and config as needed */
    for (i = 0; sc->lct[i].entry_size == I2O_LCT_ENTRYSIZE; i++) {
#ifdef PSTDEBUG
	struct i2o_get_param_reply *reply;

	printf("pstiop: LCT entry %d ", i);
	printf("class=%04x ", sc->lct[i].class);
	printf("sub=%04x ", sc->lct[i].sub_class);
	printf("localtid=%04x ", sc->lct[i].local_tid);
	printf("usertid=%04x ", sc->lct[i].user_tid);
	printf("parentid=%04x\n", sc->lct[i].parent_tid);

	if ((reply = iop_get_util_params(sc, sc->lct[i].local_tid,
					 I2O_PARAMS_OPERATION_FIELD_GET,
					 I2O_UTIL_DEVICE_IDENTITY_GROUP_NO))) {
	    struct i2o_device_identity *ident =
		(struct i2o_device_identity *)reply->result;
	    printf("pstiop: vendor=<%.16s> product=<%.16s>\n",
		   ident->vendor, ident->product);
	    printf("pstiop: description=<%.16s> revision=<%.8s>\n",
		   ident->description, ident->revision);
	    contigfree(reply, PAGE_SIZE, M_PSTIOP);
	}
#endif

	if (sc->lct[i].user_tid != I2O_TID_NONE &&
	    sc->lct[i].user_tid != I2O_TID_HOST)
	    continue;

	switch (sc->lct[i].class) {
	case I2O_CLASS_DDM:
	    if (sc->lct[i].sub_class == I2O_SUBCLASS_ISM)
		sc->ism = sc->lct[i].local_tid;
	    break;

	case I2O_CLASS_RANDOM_BLOCK_STORAGE:
	    pst_add_raid(sc, &sc->lct[i]);
	    break;
	}
    }

    /* setup and enable interrupts */
    bus_setup_intr(sc->dev, sc->r_irq, INTR_TYPE_BIO|INTR_ENTROPY|INTR_MPSAFE,
		   NULL, iop_intr, sc, &sc->handle);
    sc->reg->oqueue_intr_mask = 0x0;
}