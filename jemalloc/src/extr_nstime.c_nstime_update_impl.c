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
typedef  int /*<<< orphan*/  nstime_t ;

/* Variables and functions */
 scalar_t__ nstime_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_get (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
nstime_update_impl(nstime_t *time) {
	nstime_t old_time;

	nstime_copy(&old_time, time);
	nstime_get(time);

	/* Handle non-monotonic clocks. */
	if (unlikely(nstime_compare(&old_time, time) > 0)) {
		nstime_copy(time, &old_time);
		return true;
	}

	return false;
}