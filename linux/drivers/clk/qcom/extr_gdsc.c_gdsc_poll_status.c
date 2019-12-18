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
struct gdsc {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum gdsc_status { ____Placeholder_gdsc_status } gdsc_status ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ TIMEOUT_US ; 
 scalar_t__ gdsc_check_status (struct gdsc*,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdsc_poll_status(struct gdsc *sc, enum gdsc_status status)
{
	ktime_t start;

	start = ktime_get();
	do {
		if (gdsc_check_status(sc, status))
			return 0;
	} while (ktime_us_delta(ktime_get(), start) < TIMEOUT_US);

	if (gdsc_check_status(sc, status))
		return 0;

	return -ETIMEDOUT;
}