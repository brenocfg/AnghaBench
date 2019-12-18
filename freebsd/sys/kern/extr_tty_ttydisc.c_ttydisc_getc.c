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
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  getc_capture ; 
 int /*<<< orphan*/  getc_inject ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_nout ; 
 int /*<<< orphan*/  ttydisc_wakeup_watermark (struct tty*) ; 
 int /*<<< orphan*/  ttyhook_getc_capture (struct tty*,void*,size_t) ; 
 size_t ttyhook_getc_inject (struct tty*,void*,size_t) ; 
 scalar_t__ ttyhook_hashook (struct tty*,int /*<<< orphan*/ ) ; 
 size_t ttyoutq_read (int /*<<< orphan*/ *,void*,size_t) ; 

size_t
ttydisc_getc(struct tty *tp, void *buf, size_t len)
{

	tty_lock_assert(tp, MA_OWNED);

	if (tp->t_flags & TF_STOPPED)
		return (0);

	if (ttyhook_hashook(tp, getc_inject))
		return ttyhook_getc_inject(tp, buf, len);

	len = ttyoutq_read(&tp->t_outq, buf, len);

	if (ttyhook_hashook(tp, getc_capture))
		ttyhook_getc_capture(tp, buf, len);

	ttydisc_wakeup_watermark(tp);
	atomic_add_long(&tty_nout, len);

	return (len);
}