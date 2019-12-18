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
 int /*<<< orphan*/  MPASS (int) ; 
 int TF_BYPASS ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rint_bypass ; 
 int /*<<< orphan*/  tty_hiwat_in_block (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_nin ; 
 scalar_t__ ttyhook_hashook (struct tty*,int /*<<< orphan*/ ) ; 
 size_t ttyhook_rint_bypass (struct tty*,void const*,size_t) ; 
 int /*<<< orphan*/  ttyinq_canonicalize (int /*<<< orphan*/ *) ; 
 size_t ttyinq_write (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ) ; 

size_t
ttydisc_rint_bypass(struct tty *tp, const void *buf, size_t len)
{
	size_t ret;

	tty_lock_assert(tp, MA_OWNED);

	MPASS(tp->t_flags & TF_BYPASS);

	atomic_add_long(&tty_nin, len);

	if (ttyhook_hashook(tp, rint_bypass))
		return ttyhook_rint_bypass(tp, buf, len);

	ret = ttyinq_write(&tp->t_inq, buf, len, 0);
	ttyinq_canonicalize(&tp->t_inq);
	if (ret < len)
		tty_hiwat_in_block(tp);

	return (ret);
}