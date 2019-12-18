#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intr_config_hook {int dummy; } ;
struct TYPE_6__ {struct amr_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct amr_softc {scalar_t__ amr_nextslot; scalar_t__ amr_maxio; int /*<<< orphan*/  amr_dev; TYPE_3__ amr_ich; TYPE_1__* amr_dev_t; int /*<<< orphan*/ * amr_pass; int /*<<< orphan*/  amr_poll_command; int /*<<< orphan*/  amr_get_work; int /*<<< orphan*/  amr_submit_command; int /*<<< orphan*/  amr_poll_command1; int /*<<< orphan*/  amr_bioq; int /*<<< orphan*/  amr_cmd_clusters; int /*<<< orphan*/  amr_ready; int /*<<< orphan*/  amr_freecmds; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_5__ {struct amr_softc* si_drv1; } ;

/* Variables and functions */
 scalar_t__ AMR_IS_QUARTZ (struct amr_softc*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  amr_alloccmd_cluster (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_cdevsw ; 
 int /*<<< orphan*/  amr_describe_controller (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_init_qhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amr_init_sysctl (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_quartz_get_work ; 
 scalar_t__ amr_quartz_init (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_quartz_poll_command ; 
 int /*<<< orphan*/  amr_quartz_poll_command1 ; 
 int /*<<< orphan*/  amr_quartz_submit_command ; 
 scalar_t__ amr_query_controller (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_startup ; 
 int /*<<< orphan*/  amr_std_attach_mailbox (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_std_get_work ; 
 scalar_t__ amr_std_init (struct amr_softc*) ; 
 int /*<<< orphan*/  amr_std_poll_command ; 
 int /*<<< orphan*/  amr_std_submit_command ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 scalar_t__ config_intrhook_establish (TYPE_3__*) ; 
 int /*<<< orphan*/  debug (int,char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ *,struct amr_softc*) ; 
 int /*<<< orphan*/  linux_no_adapter ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  make_dev_alias (TYPE_1__*,char*) ; 

int
amr_attach(struct amr_softc *sc)
{
    device_t child;

    debug_called(1);

    /*
     * Initialise per-controller queues.
     */
    amr_init_qhead(&sc->amr_freecmds);
    amr_init_qhead(&sc->amr_ready);
    TAILQ_INIT(&sc->amr_cmd_clusters);
    bioq_init(&sc->amr_bioq);

    debug(2, "queue init done");

    /*
     * Configure for this controller type.
     */
    if (AMR_IS_QUARTZ(sc)) {
	sc->amr_submit_command = amr_quartz_submit_command;
	sc->amr_get_work       = amr_quartz_get_work;
	sc->amr_poll_command   = amr_quartz_poll_command;
	sc->amr_poll_command1  = amr_quartz_poll_command1;
    } else {
	sc->amr_submit_command = amr_std_submit_command;
	sc->amr_get_work       = amr_std_get_work;
	sc->amr_poll_command   = amr_std_poll_command;
	amr_std_attach_mailbox(sc);
    }

#ifdef AMR_BOARD_INIT
    if ((AMR_IS_QUARTZ(sc) ? amr_quartz_init(sc) : amr_std_init(sc)))
	return(ENXIO);
#endif

    /*
     * Allocate initial commands.
     */
    amr_alloccmd_cluster(sc);

    /*
     * Quiz controller for features and limits.
     */
    if (amr_query_controller(sc))
	return(ENXIO);

    debug(2, "controller query complete");

    /*
     * preallocate the remaining commands.
     */
    while (sc->amr_nextslot < sc->amr_maxio)
	amr_alloccmd_cluster(sc);

    /*
     * Setup sysctls.
     */
    amr_init_sysctl(sc);

    /*
     * Attach our 'real' SCSI channels to CAM.
     */
    child = device_add_child(sc->amr_dev, "amrp", -1);
    sc->amr_pass = child;
    if (child != NULL) {
	device_set_softc(child, sc);
	device_set_desc(child, "SCSI Passthrough Bus");
	bus_generic_attach(sc->amr_dev);
    }

    /*
     * Create the control device.
     */
    sc->amr_dev_t = make_dev(&amr_cdevsw, device_get_unit(sc->amr_dev), UID_ROOT, GID_OPERATOR,
			     S_IRUSR | S_IWUSR, "amr%d", device_get_unit(sc->amr_dev));
    sc->amr_dev_t->si_drv1 = sc;
    linux_no_adapter++;
    if (device_get_unit(sc->amr_dev) == 0)
	make_dev_alias(sc->amr_dev_t, "megadev0");

    /*
     * Schedule ourselves to bring the controller up once interrupts are
     * available.
     */
    bzero(&sc->amr_ich, sizeof(struct intr_config_hook));
    sc->amr_ich.ich_func = amr_startup;
    sc->amr_ich.ich_arg = sc;
    if (config_intrhook_establish(&sc->amr_ich) != 0) {
	device_printf(sc->amr_dev, "can't establish configuration hook\n");
	return(ENOMEM);
    }

    /*
     * Print a little information about the controller.
     */
    amr_describe_controller(sc);

    debug(2, "attach complete");
    return(0);
}