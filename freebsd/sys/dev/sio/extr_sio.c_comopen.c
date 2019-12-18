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
struct com_s {int fifo_image; int prev_modem_status; int last_modem_status; int /*<<< orphan*/  flags; int /*<<< orphan*/  int_ctl_port; int /*<<< orphan*/  modem_status_port; int /*<<< orphan*/  data_port; int /*<<< orphan*/  line_status_port; scalar_t__ hasfifo; int /*<<< orphan*/  loses_outints; int /*<<< orphan*/  poll_output; int /*<<< orphan*/  no_irq; int /*<<< orphan*/  poll; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ COM_IIR_TXRDYBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int FIFO_RCV_RST ; 
 int FIFO_XMT_RST ; 
 int IER_EMSC ; 
 int IER_ERLS ; 
 int IER_ERXRDY ; 
 int IER_ETXRDY ; 
 scalar_t__ ISCALLOUT (struct cdev*) ; 
 int LSR_RXRDY ; 
 int MSR_DCD ; 
 int /*<<< orphan*/  com_fifo ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sio_lock ; 
 int /*<<< orphan*/  sio_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siosettimeout () ; 
 int /*<<< orphan*/  ttyld_modem (struct tty*,int) ; 

__attribute__((used)) static int
comopen(struct tty *tp, struct cdev *dev)
{
	struct com_s	*com;
	int i;

	com = tp->t_sc;
	com->poll = com->no_irq;
	com->poll_output = com->loses_outints;
	if (com->hasfifo) {
		/*
		 * (Re)enable and drain fifos.
		 *
		 * Certain SMC chips cause problems if the fifos
		 * are enabled while input is ready.  Turn off the
		 * fifo if necessary to clear the input.  We test
		 * the input ready bit after enabling the fifos
		 * since we've already enabled them in comparam()
		 * and to handle races between enabling and fresh
		 * input.
		 */
		for (i = 0; i < 500; i++) {
			sio_setreg(com, com_fifo,
				   FIFO_RCV_RST | FIFO_XMT_RST
				   | com->fifo_image);
			/*
			 * XXX the delays are for superstitious
			 * historical reasons.  It must be less than
			 * the character time at the maximum
			 * supported speed (87 usec at 115200 bps
			 * 8N1).  Otherwise we might loop endlessly
			 * if data is streaming in.  We used to use
			 * delays of 100.  That usually worked
			 * because DELAY(100) used to usually delay
			 * for about 85 usec instead of 100.
			 */
			DELAY(50);
			if (!(inb(com->line_status_port) & LSR_RXRDY))
				break;
			sio_setreg(com, com_fifo, 0);
			DELAY(50);
			(void) inb(com->data_port);
		}
		if (i == 500)
			return (EIO);
	}

	mtx_lock_spin(&sio_lock);
	(void) inb(com->line_status_port);
	(void) inb(com->data_port);
	com->prev_modem_status = com->last_modem_status
	    = inb(com->modem_status_port);
	outb(com->int_ctl_port,
	     IER_ERXRDY | IER_ERLS | IER_EMSC
	     | (COM_IIR_TXRDYBUG(com->flags) ? 0 : IER_ETXRDY));
	mtx_unlock_spin(&sio_lock);
	siosettimeout();
	/* XXX: should be generic ? */
	if (com->prev_modem_status & MSR_DCD || ISCALLOUT(dev))
		ttyld_modem(tp, 1);
	return (0);
}