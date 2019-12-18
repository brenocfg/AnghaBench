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
struct uio {scalar_t__ uio_resid; } ;
struct TYPE_2__ {scalar_t__* c_cc; } ;
struct tty {scalar_t__ t_inlow; int /*<<< orphan*/  t_inq; TYPE_1__ t_termios; } ;

/* Variables and functions */
 scalar_t__ CMP_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICANON ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  l ; 
 int /*<<< orphan*/  tty_hiwat_in_unblock (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int ttydisc_read_canonical (struct tty*,struct uio*,int) ; 
 int ttydisc_read_raw_interbyte_timer (struct tty*,struct uio*,int) ; 
 int ttydisc_read_raw_no_timer (struct tty*,struct uio*,int) ; 
 int ttydisc_read_raw_read_timer (struct tty*,struct uio*,int,scalar_t__) ; 
 scalar_t__ ttyinq_bytescanonicalized (int /*<<< orphan*/ *) ; 
 scalar_t__ ttyinq_bytesleft (int /*<<< orphan*/ *) ; 

int
ttydisc_read(struct tty *tp, struct uio *uio, int ioflag)
{
	int error;

	tty_lock_assert(tp, MA_OWNED);

	if (uio->uio_resid == 0)
		return (0);

	if (CMP_FLAG(l, ICANON))
		error = ttydisc_read_canonical(tp, uio, ioflag);
	else if (tp->t_termios.c_cc[VTIME] == 0)
		error = ttydisc_read_raw_no_timer(tp, uio, ioflag);
	else if (tp->t_termios.c_cc[VMIN] == 0)
		error = ttydisc_read_raw_read_timer(tp, uio, ioflag,
		    uio->uio_resid);
	else
		error = ttydisc_read_raw_interbyte_timer(tp, uio, ioflag);

	if (ttyinq_bytesleft(&tp->t_inq) >= tp->t_inlow ||
	    ttyinq_bytescanonicalized(&tp->t_inq) == 0) {
		/* Unset the input watermark when we've got enough space. */
		tty_hiwat_in_unblock(tp);
	}

	return (error);
}