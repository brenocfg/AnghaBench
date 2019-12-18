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

/* Variables and functions */
 int EINVAL ; 
 int current_concurrency ; 

int
_pthread_setconcurrency(int new_level)
{
	int ret;

	if (new_level < 0) {
		ret = EINVAL;
	} else {
		current_concurrency = new_level;
		ret = 0;
	}
	return (ret);
}