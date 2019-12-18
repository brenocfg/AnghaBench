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
struct ciss_softc {TYPE_2__* ciss_id; TYPE_1__* ciss_cfg; int /*<<< orphan*/  ciss_flags; } ;
struct ciss_request {int dummy; } ;
struct TYPE_4__ {int controller_flags; int configured_logical_drives; char* running_firmware_revision; char* scsi_chip_count; int uiYetMoreControllerFlags; int PowerUPNvramFlags; } ;
struct TYPE_3__ {char* max_logical_supported; char* max_physical_supported; char* signature; char* valence; char* command_physlimit; char* interrupt_coalesce_delay; char* interrupt_coalesce_count; char* max_outstanding_commands; char* server_name; char* heartbeat; char* max_physical_per_logical; int /*<<< orphan*/  bus_types; int /*<<< orphan*/  active_method; int /*<<< orphan*/  supported_methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_BMIC_ID_CTLR ; 
#define  CISS_CMD_STATUS_DATA_OVERRUN 130 
#define  CISS_CMD_STATUS_DATA_UNDERRUN 129 
#define  CISS_CMD_STATUS_SUCCESS 128 
 int /*<<< orphan*/  CISS_FLAG_BMIC_ABORT ; 
 int /*<<< orphan*/  CISS_FLAG_FAKE_SYNCH ; 
 int /*<<< orphan*/  CISS_MALLOC_CLASS ; 
 char* CISS_MAX_LOGICAL ; 
 char* CISS_MAX_PHYSICAL ; 
 int CONTROLLER_FLAGS_BIG_MAP_SUPPORT ; 
 int EIO ; 
 int ENXIO ; 
 int PWR_UP_FLAG_JBOD_ENABLED ; 
 int YMORE_CONTROLLER_FLAGS_JBOD_SUPPORTED ; 
 scalar_t__ bootverbose ; 
 int ciss_get_bmic_request (struct ciss_softc*,struct ciss_request**,int /*<<< orphan*/ ,void**,int) ; 
 char* ciss_name_command_status (int) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,...) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_report_request (struct ciss_request*,int*,int /*<<< orphan*/ *) ; 
 int ciss_synch_request (struct ciss_request*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ciss_identify_adapter(struct ciss_softc *sc)
{
    struct ciss_request	*cr;
    int			error, command_status;

    debug_called(1);

    cr = NULL;

    /*
     * Get a request, allocate storage for the adapter data.
     */
    if ((error = ciss_get_bmic_request(sc, &cr, CISS_BMIC_ID_CTLR,
				       (void **)&sc->ciss_id,
				       sizeof(*sc->ciss_id))) != 0)
	goto out;

    /*
     * Submit the request and wait for it to complete.
     */
    if ((error = ciss_synch_request(cr, 60 * 1000)) != 0) {
	ciss_printf(sc, "error sending BMIC ID_CTLR command (%d)\n", error);
	goto out;
    }

    /*
     * Check response.
     */
    ciss_report_request(cr, &command_status, NULL);
    switch(command_status) {
    case CISS_CMD_STATUS_SUCCESS:		/* buffer right size */
	break;
    case CISS_CMD_STATUS_DATA_UNDERRUN:
    case CISS_CMD_STATUS_DATA_OVERRUN:
	ciss_printf(sc, "data over/underrun reading adapter information\n");
    default:
	ciss_printf(sc, "error reading adapter information (%s)\n",
		    ciss_name_command_status(command_status));
	error = EIO;
	goto out;
    }

    /* sanity-check reply */
    if (!(sc->ciss_id->controller_flags & CONTROLLER_FLAGS_BIG_MAP_SUPPORT)) {
	ciss_printf(sc, "adapter does not support BIG_MAP\n");
	error = ENXIO;
	goto out;
    }

#if 0
    /* XXX later revisions may not need this */
    sc->ciss_flags |= CISS_FLAG_FAKE_SYNCH;
#endif

    /* XXX only really required for old 5300 adapters? */
    sc->ciss_flags |= CISS_FLAG_BMIC_ABORT;

    /*
     * Earlier controller specs do not contain these config
     * entries, so assume that a 0 means its old and assign
     * these values to the defaults that were established 
     * when this driver was developed for them
     */
    if (sc->ciss_cfg->max_logical_supported == 0) 
        sc->ciss_cfg->max_logical_supported = CISS_MAX_LOGICAL;
    if (sc->ciss_cfg->max_physical_supported == 0) 
	sc->ciss_cfg->max_physical_supported = CISS_MAX_PHYSICAL;
    /* print information */
    if (bootverbose) {
	ciss_printf(sc, "  %d logical drive%s configured\n",
		    sc->ciss_id->configured_logical_drives,
		    (sc->ciss_id->configured_logical_drives == 1) ? "" : "s");
	ciss_printf(sc, "  firmware %4.4s\n", sc->ciss_id->running_firmware_revision);
	ciss_printf(sc, "  %d SCSI channels\n", sc->ciss_id->scsi_chip_count);

	ciss_printf(sc, "  signature '%.4s'\n", sc->ciss_cfg->signature);
	ciss_printf(sc, "  valence %d\n", sc->ciss_cfg->valence);
	ciss_printf(sc, "  supported I/O methods 0x%b\n",
		    sc->ciss_cfg->supported_methods,
		    "\20\1READY\2simple\3performant\4MEMQ\n");
	ciss_printf(sc, "  active I/O method 0x%b\n",
		    sc->ciss_cfg->active_method, "\20\2simple\3performant\4MEMQ\n");
	ciss_printf(sc, "  4G page base 0x%08x\n",
		    sc->ciss_cfg->command_physlimit);
	ciss_printf(sc, "  interrupt coalesce delay %dus\n",
		    sc->ciss_cfg->interrupt_coalesce_delay);
	ciss_printf(sc, "  interrupt coalesce count %d\n",
		    sc->ciss_cfg->interrupt_coalesce_count);
	ciss_printf(sc, "  max outstanding commands %d\n",
		    sc->ciss_cfg->max_outstanding_commands);
	ciss_printf(sc, "  bus types 0x%b\n", sc->ciss_cfg->bus_types,
		    "\20\1ultra2\2ultra3\10fibre1\11fibre2\n");
	ciss_printf(sc, "  server name '%.16s'\n", sc->ciss_cfg->server_name);
	ciss_printf(sc, "  heartbeat 0x%x\n", sc->ciss_cfg->heartbeat);
    	ciss_printf(sc, "  max logical logical volumes: %d\n", sc->ciss_cfg->max_logical_supported);
    	ciss_printf(sc, "  max physical disks supported: %d\n", sc->ciss_cfg->max_physical_supported);
    	ciss_printf(sc, "  max physical disks per logical volume: %d\n", sc->ciss_cfg->max_physical_per_logical);
	ciss_printf(sc, "  JBOD Support is %s\n", (sc->ciss_id->uiYetMoreControllerFlags & YMORE_CONTROLLER_FLAGS_JBOD_SUPPORTED) ?
			"Available" : "Unavailable");
	ciss_printf(sc, "  JBOD Mode is %s\n", (sc->ciss_id->PowerUPNvramFlags & PWR_UP_FLAG_JBOD_ENABLED) ?
			"Enabled" : "Disabled");
    }

out:
    if (error) {
	if (sc->ciss_id != NULL) {
	    free(sc->ciss_id, CISS_MALLOC_CLASS);
	    sc->ciss_id = NULL;
	}
    }
    if (cr != NULL)
	ciss_release_request(cr);
    return(error);
}