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
struct cf_level {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * timecounter ; 
 int /*<<< orphan*/  tsc_timecounter ; 

__attribute__((used)) static void
tsc_freq_changing(void *arg, const struct cf_level *level, int *status)
{

	if (*status != 0 || timecounter != &tsc_timecounter)
		return;

	printf("timecounter TSC must not be in use when "
	    "changing frequencies; change denied\n");
	*status = EBUSY;
}