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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ERESTARTSYS ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 unsigned int MSG_DONTWAIT ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  af_alg_writable (struct sock*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_set_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 scalar_t__ sk_wait_event (struct sock*,long*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int af_alg_wait_for_wmem(struct sock *sk, unsigned int flags)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int err = -ERESTARTSYS;
	long timeout;

	if (flags & MSG_DONTWAIT)
		return -EAGAIN;

	sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	add_wait_queue(sk_sleep(sk), &wait);
	for (;;) {
		if (signal_pending(current))
			break;
		timeout = MAX_SCHEDULE_TIMEOUT;
		if (sk_wait_event(sk, &timeout, af_alg_writable(sk), &wait)) {
			err = 0;
			break;
		}
	}
	remove_wait_queue(sk_sleep(sk), &wait);

	return err;
}