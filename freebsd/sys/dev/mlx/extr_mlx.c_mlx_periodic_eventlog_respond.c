#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx_softc {scalar_t__ mlx_lastevent; scalar_t__ mlx_currevent; int /*<<< orphan*/  mlx_flags; int /*<<< orphan*/  mlx_dev; } ;
struct mlx_eventlog_entry {int el_type; int el_sensekey; int el_asc; size_t el_asq; int /*<<< orphan*/  el_csi; int /*<<< orphan*/  el_information; int /*<<< orphan*/  el_target; int /*<<< orphan*/  el_channel; } ;
struct mlx_command {scalar_t__ mc_status; scalar_t__ mc_data; struct mlx_softc* mc_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX_EVENTLOG_BUSY ; 
 int /*<<< orphan*/  MLX_IO_ASSERT_LOCKED (struct mlx_softc*) ; 
#define  MLX_LOGMSG_SENSE 128 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int mlx_diagnose_command (struct mlx_command*) ; 
 int /*<<< orphan*/  mlx_periodic_eventlog_poll (struct mlx_softc*) ; 
 int /*<<< orphan*/  mlx_releasecmd (struct mlx_command*) ; 
 char** mlx_sense_messages ; 
 size_t nitems (char**) ; 

__attribute__((used)) static void
mlx_periodic_eventlog_respond(struct mlx_command *mc)
{
    struct mlx_softc		*sc = mc->mc_sc;
    struct mlx_eventlog_entry	*el = (struct mlx_eventlog_entry *)mc->mc_data;
    char			*reason;

    debug_called(1);
    MLX_IO_ASSERT_LOCKED(sc);

    sc->mlx_lastevent++;		/* next message... */
    if (mc->mc_status == 0) {

	/* handle event log message */
	switch(el->el_type) {
	    /*
	     * This is the only sort of message we understand at the moment.
	     * The tests here are probably incomplete.
	     */
	case MLX_LOGMSG_SENSE:	/* sense data */
	    /* Mylex vendor-specific message indicating a drive was killed? */
	    if ((el->el_sensekey == 9) &&
		(el->el_asc == 0x80)) {
		if (el->el_asq < nitems(mlx_sense_messages)) {
		    reason = mlx_sense_messages[el->el_asq];
		} else {
		    reason = "for unknown reason";
		}
		device_printf(sc->mlx_dev, "physical drive %d:%d killed %s\n",
			      el->el_channel, el->el_target, reason);
	    }
	    /* SCSI drive was reset? */
	    if ((el->el_sensekey == 6) && (el->el_asc == 0x29)) {
		device_printf(sc->mlx_dev, "physical drive %d:%d reset\n", 
			      el->el_channel, el->el_target);
	    }
	    /* SCSI drive error? */
	    if (!((el->el_sensekey == 0) ||
		  ((el->el_sensekey == 2) &&
		   (el->el_asc == 0x04) &&
		   ((el->el_asq == 0x01) ||
		    (el->el_asq == 0x02))))) {
		device_printf(sc->mlx_dev, "physical drive %d:%d error log: sense = %d asc = %x asq = %x\n",
			      el->el_channel, el->el_target, el->el_sensekey, el->el_asc, el->el_asq);
		device_printf(sc->mlx_dev, "  info %4D csi %4D\n", el->el_information, ":", el->el_csi, ":");
	    }
	    break;
	    
	default:
	    device_printf(sc->mlx_dev, "unknown log message type 0x%x\n", el->el_type);
	    break;
	}
    } else {
	device_printf(sc->mlx_dev, "error reading message log - %s\n", mlx_diagnose_command(mc));
	/* give up on all the outstanding messages, as we may have come unsynched */
	sc->mlx_lastevent = sc->mlx_currevent;
    }
	
    /* dispose of command and data */
    free(mc->mc_data, M_DEVBUF);
    mlx_releasecmd(mc);

    /* is there another message to obtain? */
    if (sc->mlx_lastevent != sc->mlx_currevent) {
	mlx_periodic_eventlog_poll(sc);
    } else {
	/* clear log-busy status */
	sc->mlx_flags &= ~MLX_EVENTLOG_BUSY;
    }
}