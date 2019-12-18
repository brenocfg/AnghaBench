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
struct drbd_device {int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  ap_pending_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_IF_CNT_IS_NEGATIVE (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  ap_pending_cnt ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _dec_ap_pending(struct drbd_device *device, const char *func, int line)
{
	if (atomic_dec_and_test(&device->ap_pending_cnt))
		wake_up(&device->misc_wait);
	ERR_IF_CNT_IS_NEGATIVE(ap_pending_cnt, func, line);
}