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
typedef  int /*<<< orphan*/  u_char ;
struct tty {int t_ififosize; int t_ispeedwat; int t_ospeedwat; } ;
struct com_s {int ibufsize; scalar_t__ ibufold; scalar_t__ ibuf; scalar_t__ iptr; int ierroff; int /*<<< orphan*/ * ihighwater; int /*<<< orphan*/ * ibufend; struct tty* tp; } ;
typedef  int speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  COM_LOCK () ; 
 int /*<<< orphan*/  COM_UNLOCK () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  cyinput (struct com_s*) ; 
 int hz ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cysetwater(struct com_s *com, speed_t speed)
{
	int		cp4ticks;
	u_char		*ibuf;
	int		ibufsize;
	struct tty	*tp;

	/*
	 * Make the buffer size large enough to handle a softtty interrupt
	 * latency of about 2 ticks without loss of throughput or data
	 * (about 3 ticks if input flow control is not used or not honoured,
	 * but a bit less for CS5-CS7 modes).
	 */
	cp4ticks = speed / 10 / hz * 4;
	for (ibufsize = 128; ibufsize < cp4ticks;)
		ibufsize <<= 1;
	if (ibufsize == com->ibufsize) {
		return (0);
	}

	/*
	 * Allocate input buffer.  The extra factor of 2 in the size is
	 * to allow for an error byte for each input byte.
	 */
	ibuf = malloc(2 * ibufsize, M_DEVBUF, M_NOWAIT);
	if (ibuf == NULL) {
		return (ENOMEM);
	}

	/* Initialize non-critical variables. */
	com->ibufold = com->ibuf;
	com->ibufsize = ibufsize;
	tp = com->tp;
	if (tp != NULL) {
		tp->t_ififosize = 2 * ibufsize;
		tp->t_ispeedwat = (speed_t)-1;
		tp->t_ospeedwat = (speed_t)-1;
	}

	/*
	 * Read current input buffer, if any.  Continue with interrupts
	 * disabled.
	 */
	critical_enter();
	COM_LOCK();
	if (com->iptr != com->ibuf)
		cyinput(com);

	/*-
	 * Initialize critical variables, including input buffer watermarks.
	 * The external device is asked to stop sending when the buffer
	 * exactly reaches high water, or when the high level requests it.
	 * The high level is notified immediately (rather than at a later
	 * clock tick) when this watermark is reached.
	 * The buffer size is chosen so the watermark should almost never
	 * be reached.
	 * The low watermark is invisibly 0 since the buffer is always
	 * emptied all at once.
	 */
	com->iptr = com->ibuf = ibuf;
	com->ibufend = ibuf + ibufsize;
	com->ierroff = ibufsize;
	com->ihighwater = ibuf + 3 * ibufsize / 4;

	COM_UNLOCK();
	critical_exit();
	return (0);
}