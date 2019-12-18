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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  pow2ns_to_ts (int,struct timespec*) ; 
 int tvtohz (struct timeval*) ; 

__attribute__((used)) static int
pow2ns_to_ticks(int pow2ns)
{
	struct timeval tv;
	struct timespec ts;

	pow2ns_to_ts(pow2ns, &ts);
	TIMESPEC_TO_TIMEVAL(&tv, &ts);
	return (tvtohz(&tv));
}