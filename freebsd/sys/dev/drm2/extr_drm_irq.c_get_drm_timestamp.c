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
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_timestamp_monotonic ; 
 int /*<<< orphan*/  ktime_get_monotonic_offset () ; 
 struct timeval ktime_sub (struct timeval,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 

__attribute__((used)) static struct timeval get_drm_timestamp(void)
{
	struct timeval now;

	microtime(&now);
#ifdef FREEBSD_NOTYET
	if (!drm_timestamp_monotonic)
		now = ktime_sub(now, ktime_get_monotonic_offset());
#endif /* defined(FREEBSD_NOTYET) */

	return now;
}