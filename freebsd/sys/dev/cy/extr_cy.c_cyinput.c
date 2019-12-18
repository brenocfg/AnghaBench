#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_2__ {scalar_t__ c_cc; } ;
struct tty {int t_state; scalar_t__ t_ihiwat; int t_iflag; int t_rawcc; scalar_t__* t_cc; int /*<<< orphan*/  t_lflag; TYPE_1__ t_rawq; } ;
struct com_s {int* ibuf; int* iptr; int state; size_t ierroff; int mcr_image; int mcr_rts; int /*<<< orphan*/  mcr_rts_reg; int /*<<< orphan*/ * delta_error_counts; struct tty* tp; } ;

/* Variables and functions */
 int CD1400_RDSR_BREAK ; 
 int CD1400_RDSR_FE ; 
 int CD1400_RDSR_OE ; 
 int CD1400_RDSR_PE ; 
 size_t CE_TTY_BUF_OVERFLOW ; 
 int /*<<< orphan*/  COM_LOCK () ; 
 int /*<<< orphan*/  COM_UNLOCK () ; 
 int CS_RTS_IFLOW ; 
 int /*<<< orphan*/  FLUSHO ; 
 int IXANY ; 
 int IXOFF ; 
 int TS_CAN_BYPASS_L_RINT ; 
 int TS_ISOPEN ; 
 int TS_TBLOCK ; 
 int TS_TTSTOP ; 
 int TTY_BI ; 
 int TTY_FE ; 
 int TTY_OE ; 
 int TTY_PE ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 scalar_t__ b_to_q (char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  cd_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  cy_events ; 
 int /*<<< orphan*/  cystart (struct tty*) ; 
 int tk_nin ; 
 int tk_rawcc ; 
 int /*<<< orphan*/  ttwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttyblock (struct tty*) ; 
 int /*<<< orphan*/  ttyld_rint (struct tty*,int) ; 

__attribute__((used)) static void
cyinput(struct com_s *com)
{
	u_char		*buf;
	int		incc;
	u_char		line_status;
	int		recv_data;
	struct tty	*tp;

	buf = com->ibuf;
	tp = com->tp;
	if (!(tp->t_state & TS_ISOPEN)) {
		cy_events -= (com->iptr - com->ibuf);
		com->iptr = com->ibuf;
		return;
	}
	if (tp->t_state & TS_CAN_BYPASS_L_RINT) {
		/*
		 * Avoid the grotesquely inefficient lineswitch routine
		 * (ttyinput) in "raw" mode.  It usually takes about 450
		 * instructions (that's without canonical processing or echo!).
		 * slinput is reasonably fast (usually 40 instructions plus
		 * call overhead).
		 */

		do {
			/*
			 * This may look odd, but it is using save-and-enable
			 * semantics instead of the save-and-disable semantics
			 * that are used everywhere else.
			 */
			COM_UNLOCK();
			critical_exit();
			incc = com->iptr - buf;
			if (tp->t_rawq.c_cc + incc > tp->t_ihiwat
			    && (com->state & CS_RTS_IFLOW
				|| tp->t_iflag & IXOFF)
			    && !(tp->t_state & TS_TBLOCK))
				ttyblock(tp);
			com->delta_error_counts[CE_TTY_BUF_OVERFLOW]
				+= b_to_q((char *)buf, incc, &tp->t_rawq);
			buf += incc;
			tk_nin += incc;
			tk_rawcc += incc;
			tp->t_rawcc += incc;
			ttwakeup(tp);
			if (tp->t_state & TS_TTSTOP
			    && (tp->t_iflag & IXANY
				|| tp->t_cc[VSTART] == tp->t_cc[VSTOP])) {
				tp->t_state &= ~TS_TTSTOP;
				tp->t_lflag &= ~FLUSHO;
				cystart(tp);
			}
			critical_enter();
			COM_LOCK();
		} while (buf < com->iptr);
	} else {
		do {
			/*
			 * This may look odd, but it is using save-and-enable
			 * semantics instead of the save-and-disable semantics
			 * that are used everywhere else.
			 */
			COM_UNLOCK();
			critical_exit();
			line_status = buf[com->ierroff];
			recv_data = *buf++;
			if (line_status
			    & (CD1400_RDSR_BREAK | CD1400_RDSR_FE | CD1400_RDSR_OE | CD1400_RDSR_PE)) {
				if (line_status & CD1400_RDSR_BREAK)
					recv_data |= TTY_BI;
				if (line_status & CD1400_RDSR_FE)
					recv_data |= TTY_FE;
				if (line_status & CD1400_RDSR_OE)
					recv_data |= TTY_OE;
				if (line_status & CD1400_RDSR_PE)
					recv_data |= TTY_PE;
			}
			ttyld_rint(tp, recv_data);
			critical_enter();
			COM_LOCK();
		} while (buf < com->iptr);
	}
	cy_events -= (com->iptr - com->ibuf);
	com->iptr = com->ibuf;

	/*
	 * There is now room for another low-level buffer full of input,
	 * so enable RTS if it is now disabled and there is room in the
	 * high-level buffer.
	 */
	if ((com->state & CS_RTS_IFLOW) && !(com->mcr_image & com->mcr_rts) &&
	    !(tp->t_state & TS_TBLOCK))
		cd_setreg(com, com->mcr_rts_reg,
			  com->mcr_image |= com->mcr_rts);
}