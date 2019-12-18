#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ max_concurrent_cmds; } ;
struct TYPE_16__ {int max_cmds; int ffdc_resetcount; size_t adapter_type; int /*<<< orphan*/  timer; TYPE_4__* device_file; int /*<<< orphan*/  dev; TYPE_1__ adapter_info; int /*<<< orphan*/  ffdc_resettime; scalar_t__ (* ips_adapter_reinit ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sg_dmatag; int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  adapter_dmatag; int /*<<< orphan*/  command_dmatag; } ;
typedef  TYPE_2__ ips_softc_t ;
struct TYPE_17__ {TYPE_2__* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  DEVICE_PRINTF (int,int /*<<< orphan*/ ,char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 size_t IPS_ADAPTER_MAX_T ; 
 scalar_t__ IPS_COMMAND_LEN ; 
 scalar_t__ IPS_MAX_IOBUF_SIZE ; 
 int IPS_MAX_SG_ELEMENTS ; 
 scalar_t__ IPS_MAX_SG_LEN ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busdma_lock_mutex ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hz ; 
 int /*<<< orphan*/  ips_adapter_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * ips_adapter_name ; 
 int /*<<< orphan*/  ips_cdevsw ; 
 int /*<<< orphan*/  ips_cmdqueue_free (TYPE_2__*) ; 
 scalar_t__ ips_cmdqueue_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ips_diskdev_init (TYPE_2__*) ; 
 int ips_ffdc_reset (TYPE_2__*) ; 
 int ips_get_adapter_info (TYPE_2__*) ; 
 int ips_get_drive_info (TYPE_2__*) ; 
 int /*<<< orphan*/  ips_timeout ; 
 int /*<<< orphan*/  ips_update_nvram (TYPE_2__*) ; 
 TYPE_4__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microtime (int /*<<< orphan*/ *) ; 
 int min (int,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int ips_adapter_init(ips_softc_t *sc)
{
        int i;
        DEVICE_PRINTF(1,sc->dev, "initializing\n");

        if (bus_dma_tag_create(	/* parent    */	sc->adapter_dmatag,
				/* alignemnt */	1,
				/* boundary  */	0,
				/* lowaddr   */	BUS_SPACE_MAXADDR_32BIT,
				/* highaddr  */	BUS_SPACE_MAXADDR,
				/* filter    */	NULL,
				/* filterarg */	NULL,
				/* maxsize   */	IPS_COMMAND_LEN + 
						    IPS_MAX_SG_LEN,
				/* numsegs   */	1,
				/* maxsegsize*/	IPS_COMMAND_LEN + 
						    IPS_MAX_SG_LEN,
				/* flags     */	0,
				/* lockfunc  */ NULL,
				/* lockarg   */ NULL,
				&sc->command_dmatag) != 0) {
                device_printf(sc->dev, "can't alloc command dma tag\n");
		goto error;
        }
	if (bus_dma_tag_create(	/* parent    */	sc->adapter_dmatag,
				/* alignemnt */	1,
				/* boundary  */	0,
				/* lowaddr   */	BUS_SPACE_MAXADDR_32BIT,
				/* highaddr  */	BUS_SPACE_MAXADDR,
				/* filter    */	NULL,
				/* filterarg */	NULL,
				/* maxsize   */	IPS_MAX_IOBUF_SIZE,
				/* numsegs   */	IPS_MAX_SG_ELEMENTS,
				/* maxsegsize*/	IPS_MAX_IOBUF_SIZE,
				/* flags     */	0,
				/* lockfunc  */ busdma_lock_mutex,
				/* lockarg   */ &sc->queue_mtx,
				&sc->sg_dmatag) != 0) {
		device_printf(sc->dev, "can't alloc SG dma tag\n");
		goto error;
	}
	/* create one command buffer until we know how many commands this card
           can handle */
	sc->max_cmds = 1;
	ips_cmdqueue_init(sc);

	if(sc->ips_adapter_reinit(sc, 0))
		goto error;

	/* initialize ffdc values */
	microtime(&sc->ffdc_resettime);
	sc->ffdc_resetcount = 1;
	if ((i = ips_ffdc_reset(sc)) != 0) {
		device_printf(sc->dev, "failed to send ffdc reset to device (%d)\n", i);
		goto error;
	}
	if ((i = ips_get_adapter_info(sc)) != 0) {
		device_printf(sc->dev, "failed to get adapter configuration data from device (%d)\n", i);
		goto error;
	}
	ips_update_nvram(sc); /* no error check as failure doesn't matter */
	if(sc->adapter_type > 0 && sc->adapter_type <= IPS_ADAPTER_MAX_T){
		device_printf(sc->dev, "adapter type: %s\n", ips_adapter_name[sc->adapter_type]);
	}
 	if ((i = ips_get_drive_info(sc)) != 0) {
		device_printf(sc->dev, "failed to get drive configuration data from device (%d)\n", i);
		goto error;
	}

        ips_cmdqueue_free(sc);
	if(sc->adapter_info.max_concurrent_cmds)
        	sc->max_cmds = min(128, sc->adapter_info.max_concurrent_cmds);
	else
		sc->max_cmds = 32;
        if(ips_cmdqueue_init(sc)){
		device_printf(sc->dev, "failed to initialize command buffers\n");
		goto error;
	}
        sc->device_file = make_dev(&ips_cdevsw, device_get_unit(sc->dev), UID_ROOT, GID_OPERATOR,
                                        S_IRUSR | S_IWUSR, "ips%d", device_get_unit(sc->dev));
	sc->device_file->si_drv1 = sc;
	ips_diskdev_init(sc);
	callout_reset(&sc->timer, 10 * hz, ips_timeout, sc);
        return 0;

error:
	ips_adapter_free(sc);
	return ENXIO;
}