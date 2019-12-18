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
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 scalar_t__ errno ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int
do_select(struct timespec *delay, struct timespec *remain)
{
	int ret;
	struct timeval tv;

	TIMESPEC_TO_TIMEVAL(&tv, delay);
	if (select(0, NULL, NULL, NULL, &tv) == -1)
		ret = (errno == EINTR ? 0 : errno);
	else
		ret = 0;
	return ret;
}