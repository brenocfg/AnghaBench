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
typedef  scalar_t__ time_t ;
struct timespec {scalar_t__ tv_sec; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int ENOENT ; 
 int kern_clock_gettime (struct thread*,int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ wd_lastpat ; 
 int /*<<< orphan*/  wd_lastpat_valid ; 

__attribute__((used)) static int
wd_get_time_left(struct thread *td, time_t *remainp)
{
	struct timespec ts;
	int error;

	error = kern_clock_gettime(td, CLOCK_MONOTONIC_FAST, &ts);
	if (error)
		return (error);
	if (!wd_lastpat_valid)
		return (ENOENT);
	*remainp = ts.tv_sec - wd_lastpat;
	return (0);
}