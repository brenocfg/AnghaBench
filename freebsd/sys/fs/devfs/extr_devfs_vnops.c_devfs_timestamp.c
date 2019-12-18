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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 scalar_t__ devfs_dotimes ; 
 scalar_t__ time_second ; 
 int /*<<< orphan*/  vfs_timestamp (struct timespec*) ; 

__attribute__((used)) static void
devfs_timestamp(struct timespec *tsp)
{
	time_t ts;

	if (devfs_dotimes) {
		vfs_timestamp(tsp);
	} else {
		ts = time_second;
		if (tsp->tv_sec != ts) {
			tsp->tv_sec = ts;
			tsp->tv_nsec = 0;
		}
	}
}