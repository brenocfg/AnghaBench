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
struct com_s {int etc; int intr_enable; } ;

/* Variables and functions */
 int CD1400_ETC_SENDBREAK ; 
 int CD1400_ETC_STOPBREAK ; 
 int /*<<< orphan*/  CD1400_SRER ; 
 int CD1400_SRER_TXMPTY ; 
 int CD1400_SRER_TXRDY ; 
 int /*<<< orphan*/  COM_LOCK () ; 
 int /*<<< orphan*/  COM_UNLOCK () ; 
 int ETC_BREAK_ENDED ; 
 int ETC_BREAK_ENDING ; 
 int ETC_BREAK_STARTED ; 
 int ETC_BREAK_STARTING ; 
 int ETC_NONE ; 
 int PCATCH ; 
 int TTIPRI ; 
 int /*<<< orphan*/  cd_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 scalar_t__ tsleep (int*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cd_etc(struct com_s *com, int etc)
{

	/*
	 * We can't change the hardware's ETC state while there are any
	 * characters in the tx fifo, since those characters would be
	 * interpreted as commands!  Unputting characters from the fifo
	 * is difficult, so we wait up to 12 character times for the fifo
	 * to drain.  The command will be delayed for up to 2 character
	 * times for the tx to become empty.  Unputting characters from
	 * the tx holding and shift registers is impossible, so we wait
	 * for the tx to become empty so that the command is sure to be
	 * executed soon after we issue it.
	 */
	critical_enter();
	COM_LOCK();
	if (com->etc == etc)
		goto wait;
	if ((etc == CD1400_ETC_SENDBREAK
	    && (com->etc == ETC_BREAK_STARTING
		|| com->etc == ETC_BREAK_STARTED))
	    || (etc == CD1400_ETC_STOPBREAK
	       && (com->etc == ETC_BREAK_ENDING || com->etc == ETC_BREAK_ENDED
		   || com->etc == ETC_NONE))) {
		COM_UNLOCK();
		critical_exit();
		return;
	}
	com->etc = etc;
	cd_setreg(com, CD1400_SRER,
		  com->intr_enable
		  = (com->intr_enable & ~CD1400_SRER_TXRDY) | CD1400_SRER_TXMPTY);
wait:
	COM_UNLOCK();
	critical_exit();
	while (com->etc == etc
	       && tsleep(&com->etc, TTIPRI | PCATCH, "cyetc", 0) == 0)
		continue;
}