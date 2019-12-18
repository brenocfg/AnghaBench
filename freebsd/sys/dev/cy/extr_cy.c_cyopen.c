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
struct tty {struct com_s* t_sc; } ;
struct com_s {int unit; int channel_control; int intr_enable; int /*<<< orphan*/  last_modem_status; int /*<<< orphan*/  prev_modem_status; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int CD1400_CCR_CHANRESET ; 
 int CD1400_CCR_CMDRESET ; 
 int /*<<< orphan*/  CD1400_LIVR ; 
 int /*<<< orphan*/  CD1400_MSVR2 ; 
 int /*<<< orphan*/  CD1400_SRER ; 
 int CD1400_SRER_MDMCH ; 
 int CD1400_SRER_RXDATA ; 
 int CD1400_xIVR_CHAN ; 
 int CD1400_xIVR_CHAN_SHIFT ; 
 int /*<<< orphan*/  COM_LOCK () ; 
 int /*<<< orphan*/  COM_UNLOCK () ; 
 int /*<<< orphan*/  cd1400_channel_cmd (struct com_s*,int) ; 
 int /*<<< orphan*/  cd_getreg (struct com_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  cysettimeout () ; 
 int spltty () ; 

__attribute__((used)) static int
cyopen(struct tty *tp, struct cdev *dev)
{
	struct com_s	*com;
	int		s;

	com = tp->t_sc;
	s = spltty();
	/*
	 * We jump to this label after all non-interrupted sleeps to pick
	 * up any changes of the device state.
	 */

	/* Encode per-board unit in LIVR for access in intr routines. */
	cd_setreg(com, CD1400_LIVR,
		  (com->unit & CD1400_xIVR_CHAN) << CD1400_xIVR_CHAN_SHIFT);

	/*
	 * Flush fifos.  This requires a full channel reset which
	 * also disables the transmitter and receiver.  Recover
	 * from this.
	 */
	cd1400_channel_cmd(com,
			   CD1400_CCR_CMDRESET | CD1400_CCR_CHANRESET);
	cd1400_channel_cmd(com, com->channel_control);

	critical_enter();
	COM_LOCK();
	com->prev_modem_status = com->last_modem_status
	    = cd_getreg(com, CD1400_MSVR2);
	cd_setreg(com, CD1400_SRER,
		  com->intr_enable
		  = CD1400_SRER_MDMCH | CD1400_SRER_RXDATA);
	COM_UNLOCK();
	critical_exit();
	cysettimeout();
	return (0);
}