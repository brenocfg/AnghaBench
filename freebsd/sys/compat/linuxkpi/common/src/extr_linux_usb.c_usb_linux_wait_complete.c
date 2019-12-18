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
struct urb {int transfer_flags; int /*<<< orphan*/  cv_wait; } ;

/* Variables and functions */
 int URB_IS_SLEEPING ; 
 int URB_WAIT_WAKEUP ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usb_linux_wait_complete(struct urb *urb)
{
	if (urb->transfer_flags & URB_IS_SLEEPING) {
		cv_signal(&urb->cv_wait);
	}
	urb->transfer_flags &= ~URB_WAIT_WAKEUP;
}