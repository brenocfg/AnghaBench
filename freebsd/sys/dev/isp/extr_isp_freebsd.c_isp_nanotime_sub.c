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
typedef  scalar_t__ uint64_t ;
struct timespec {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_NANOSEC (struct timespec*) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 

uint64_t
isp_nanotime_sub(struct timespec *b, struct timespec *a)
{
	uint64_t elapsed;
	struct timespec x;

	timespecsub(b, a, &x);
	elapsed = GET_NANOSEC(&x);
	if (elapsed == 0)
		elapsed++;
	return (elapsed);
}