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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct amr_softc {int amr_maxdrives; int amr_ld_del_supported; int /*<<< orphan*/  amr_maxio; TYPE_3__* amr_drive; int /*<<< orphan*/  amr_maxchan; int /*<<< orphan*/  amr_dev; int /*<<< orphan*/  amr_type; scalar_t__ support_ext_cdb; } ;
struct TYPE_5__ {int /*<<< orphan*/  aa_maxio; int /*<<< orphan*/  aa_channels; } ;
struct TYPE_4__ {int al_numdrives; int* al_size; int /*<<< orphan*/ * al_properties; int /*<<< orphan*/ * al_state; } ;
struct amr_prodinfo {int ae_numldrives; int* ae_drivesize; TYPE_2__ ae_adapter; TYPE_1__ ae_ldrv; scalar_t__ ae_signature; int /*<<< orphan*/  ap_maxio; int /*<<< orphan*/  ap_nschan; int /*<<< orphan*/ * ae_driveprop; int /*<<< orphan*/ * ae_drivestate; } ;
struct amr_enquiry3 {int ae_numldrives; int* ae_drivesize; TYPE_2__ ae_adapter; TYPE_1__ ae_ldrv; scalar_t__ ae_signature; int /*<<< orphan*/  ap_maxio; int /*<<< orphan*/  ap_nschan; int /*<<< orphan*/ * ae_driveprop; int /*<<< orphan*/ * ae_drivestate; } ;
struct amr_enquiry {int ae_numldrives; int* ae_drivesize; TYPE_2__ ae_adapter; TYPE_1__ ae_ldrv; scalar_t__ ae_signature; int /*<<< orphan*/  ap_maxio; int /*<<< orphan*/  ap_nschan; int /*<<< orphan*/ * ae_driveprop; int /*<<< orphan*/ * ae_drivestate; } ;
struct TYPE_6__ {int al_size; int /*<<< orphan*/  al_properties; int /*<<< orphan*/  al_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_CMD_CONFIG ; 
 int /*<<< orphan*/  AMR_CMD_ENQUIRY ; 
 int /*<<< orphan*/  AMR_CMD_EXT_ENQUIRY2 ; 
 int /*<<< orphan*/  AMR_CONFIG_ENQ3 ; 
 int /*<<< orphan*/  AMR_CONFIG_ENQ3_SOLICITED_FULL ; 
 int /*<<< orphan*/  AMR_CONFIG_PRODUCT_INFO ; 
 int /*<<< orphan*/  AMR_LIMITCMD ; 
 int AMR_MAXLD ; 
 int /*<<< orphan*/  AMR_TYPE_40LD ; 
 int /*<<< orphan*/  FC_DEL_LOGDRV ; 
 int /*<<< orphan*/  M_AMR ; 
 int /*<<< orphan*/  OP_SUP_DEL_LOGDRV ; 
 struct amr_prodinfo* amr_enquiry (struct amr_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ amr_support_ext_cdb (struct amr_softc*) ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct amr_prodinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amr_query_controller(struct amr_softc *sc)
{
    struct amr_enquiry3	*aex;
    struct amr_prodinfo	*ap;
    struct amr_enquiry	*ae;
    int			ldrv;
    int			status;

    /*
     * Greater than 10 byte cdb support
     */
    sc->support_ext_cdb = amr_support_ext_cdb(sc);

    if(sc->support_ext_cdb) {
	debug(2,"supports extended CDBs.");
    }

    /* 
     * Try to issue an ENQUIRY3 command 
     */
    if ((aex = amr_enquiry(sc, 2048, AMR_CMD_CONFIG, AMR_CONFIG_ENQ3, 
			   AMR_CONFIG_ENQ3_SOLICITED_FULL, &status)) != NULL) {

	/*
	 * Fetch current state of logical drives.
	 */
	for (ldrv = 0; ldrv < aex->ae_numldrives; ldrv++) {
	    sc->amr_drive[ldrv].al_size       = aex->ae_drivesize[ldrv];
	    sc->amr_drive[ldrv].al_state      = aex->ae_drivestate[ldrv];
	    sc->amr_drive[ldrv].al_properties = aex->ae_driveprop[ldrv];
	    debug(2, "  drive %d: %d state %x properties %x\n", ldrv, sc->amr_drive[ldrv].al_size,
		  sc->amr_drive[ldrv].al_state, sc->amr_drive[ldrv].al_properties);
	}
	free(aex, M_AMR);

	/*
	 * Get product info for channel count.
	 */
	if ((ap = amr_enquiry(sc, 2048, AMR_CMD_CONFIG, AMR_CONFIG_PRODUCT_INFO, 0, &status)) == NULL) {
	    device_printf(sc->amr_dev, "can't obtain product data from controller\n");
	    return(1);
	}
	sc->amr_maxdrives = 40;
	sc->amr_maxchan = ap->ap_nschan;
	sc->amr_maxio = ap->ap_maxio;
	sc->amr_type |= AMR_TYPE_40LD;
	free(ap, M_AMR);

	ap = amr_enquiry(sc, 0, FC_DEL_LOGDRV, OP_SUP_DEL_LOGDRV, 0, &status);
	if (ap != NULL)
	    free(ap, M_AMR);
	if (!status) {
	    sc->amr_ld_del_supported = 1;
	    device_printf(sc->amr_dev, "delete logical drives supported by controller\n");
	}
    } else {

	/* failed, try the 8LD ENQUIRY commands */
	if ((ae = (struct amr_enquiry *)amr_enquiry(sc, 2048, AMR_CMD_EXT_ENQUIRY2, 0, 0, &status)) == NULL) {
	    if ((ae = (struct amr_enquiry *)amr_enquiry(sc, 2048, AMR_CMD_ENQUIRY, 0, 0, &status)) == NULL) {
		device_printf(sc->amr_dev, "can't obtain configuration data from controller\n");
		return(1);
	    }
	    ae->ae_signature = 0;
	}

	/*
	 * Fetch current state of logical drives.
	 */
	for (ldrv = 0; ldrv < ae->ae_ldrv.al_numdrives; ldrv++) {
	    sc->amr_drive[ldrv].al_size       = ae->ae_ldrv.al_size[ldrv];
	    sc->amr_drive[ldrv].al_state      = ae->ae_ldrv.al_state[ldrv];
	    sc->amr_drive[ldrv].al_properties = ae->ae_ldrv.al_properties[ldrv];
	    debug(2, "  drive %d: %d state %x properties %x\n", ldrv, sc->amr_drive[ldrv].al_size,
		  sc->amr_drive[ldrv].al_state, sc->amr_drive[ldrv].al_properties);
	}

	sc->amr_maxdrives = 8;
	sc->amr_maxchan = ae->ae_adapter.aa_channels;
	sc->amr_maxio = ae->ae_adapter.aa_maxio;
	free(ae, M_AMR);
    }

    /*
     * Mark remaining drives as unused.
     */
    for (; ldrv < AMR_MAXLD; ldrv++)
	sc->amr_drive[ldrv].al_size = 0xffffffff;

    /* 
     * Cap the maximum number of outstanding I/Os.  AMI's Linux driver doesn't trust
     * the controller's reported value, and lockups have been seen when we do.
     */
    sc->amr_maxio = imin(sc->amr_maxio, AMR_LIMITCMD);

    return(0);
}