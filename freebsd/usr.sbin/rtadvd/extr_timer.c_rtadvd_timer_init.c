#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_3__ {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_timer ; 
 TYPE_1__ tm_limit ; 
 TYPE_1__ tm_max ; 

void
rtadvd_timer_init(void)
{
	/* Generate maximum time in timespec. */
	tm_limit.tv_sec = (-1) & ~((time_t)1 << ((sizeof(tm_max.tv_sec) * 8) - 1));
	tm_limit.tv_nsec = (-1) & ~((long)1 << ((sizeof(tm_max.tv_nsec) * 8) - 1));
	tm_max = tm_limit;
	TAILQ_INIT(&ra_timer);
}