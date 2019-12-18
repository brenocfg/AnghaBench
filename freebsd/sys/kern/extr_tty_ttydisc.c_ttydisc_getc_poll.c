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
struct tty {int t_flags; int /*<<< orphan*/  t_outq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int TF_STOPPED ; 
 int /*<<< orphan*/  getc_poll ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 size_t ttyhook_getc_poll (struct tty*) ; 
 scalar_t__ ttyhook_hashook (struct tty*,int /*<<< orphan*/ ) ; 
 size_t ttyoutq_bytesused (int /*<<< orphan*/ *) ; 

size_t
ttydisc_getc_poll(struct tty *tp)
{

	tty_lock_assert(tp, MA_OWNED);

	if (tp->t_flags & TF_STOPPED)
		return (0);

	if (ttyhook_hashook(tp, getc_poll))
		return ttyhook_getc_poll(tp);

	return ttyoutq_bytesused(&tp->t_outq);
}