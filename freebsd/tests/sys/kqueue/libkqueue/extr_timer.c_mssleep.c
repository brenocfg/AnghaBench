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
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_TO_US (int) ; 
 int /*<<< orphan*/  US_TO_NS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 

void
mssleep(int t)
{
    struct timespec stime = {
        .tv_sec = 0,
        .tv_nsec = US_TO_NS(MS_TO_US(t)),
    };

    nanosleep(&stime, NULL);
}