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
struct tty {int t_drainwait; int /*<<< orphan*/  t_outq; int /*<<< orphan*/  t_outwait; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int SBT_1S ; 
 int /*<<< orphan*/  getc_inject ; 
 scalar_t__ getsbinuptime () ; 
 int hz ; 
 int tty_timedwait (struct tty*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttydevsw_busy (struct tty*) ; 
 int /*<<< orphan*/  ttydevsw_outwakeup (struct tty*) ; 
 scalar_t__ ttyhook_hashook (struct tty*,int /*<<< orphan*/ ) ; 
 size_t ttyoutq_bytesused (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tty_drain(struct tty *tp, int leaving)
{
	sbintime_t timeout_at;
	size_t bytes;
	int error;

	if (ttyhook_hashook(tp, getc_inject))
		/* buffer is inaccessible */
		return (0);

	/*
	 * For close(), use the recent historic timeout of "1 second without
	 * making progress".  For tcdrain(), use t_drainwait as the timeout,
	 * with zero meaning "no timeout" which gives POSIX behavior.
	 */
	if (leaving)
		timeout_at = getsbinuptime() + SBT_1S;
	else if (tp->t_drainwait != 0)
		timeout_at = getsbinuptime() + SBT_1S * tp->t_drainwait;
	else
		timeout_at = 0;

	/*
	 * Poll the output buffer and the hardware for completion, at 10 Hz.
	 * Polling is required for devices which are not able to signal an
	 * interrupt when the transmitter becomes idle (most USB serial devs).
	 * The unusual structure of this loop ensures we check for busy one more
	 * time after tty_timedwait() returns EWOULDBLOCK, so that success has
	 * higher priority than timeout if the IO completed in the last 100mS.
	 */
	error = 0;
	bytes = ttyoutq_bytesused(&tp->t_outq);
	for (;;) {
		if (ttyoutq_bytesused(&tp->t_outq) == 0 && !ttydevsw_busy(tp))
			return (0);
		if (error != 0)
			return (error);
		ttydevsw_outwakeup(tp);
		error = tty_timedwait(tp, &tp->t_outwait, hz / 10);
		if (error != 0 && error != EWOULDBLOCK)
			return (error);
		else if (timeout_at == 0 || getsbinuptime() < timeout_at)
			error = 0;
		else if (leaving && ttyoutq_bytesused(&tp->t_outq) < bytes) {
			/* In close, making progress, grant an extra second. */
			error = 0;
			timeout_at += SBT_1S;
			bytes = ttyoutq_bytesused(&tp->t_outq);
		}
	}
}