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
struct tty {int t_flags; int /*<<< orphan*/  t_inq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int TF_HIWAT_IN ; 
 int /*<<< orphan*/  rint_poll ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 scalar_t__ ttyhook_hashook (struct tty*,int /*<<< orphan*/ ) ; 
 size_t ttyhook_rint_poll (struct tty*) ; 
 size_t ttyinq_bytesleft (int /*<<< orphan*/ *) ; 

size_t
ttydisc_rint_poll(struct tty *tp)
{
	size_t l;

	tty_lock_assert(tp, MA_OWNED);

	if (ttyhook_hashook(tp, rint_poll))
		return ttyhook_rint_poll(tp);

	/*
	 * XXX: Still allow character input when there's no space in the
	 * buffers, but we haven't entered the high watermark. This is
	 * to allow backspace characters to be inserted when in
	 * canonical mode.
	 */
	l = ttyinq_bytesleft(&tp->t_inq);
	if (l == 0 && (tp->t_flags & TF_HIWAT_IN) == 0)
		return (1);

	return (l);
}