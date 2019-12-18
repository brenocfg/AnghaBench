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
typedef  int uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  t0; int /*<<< orphan*/  t1; } ;
typedef  TYPE_1__ timedelta_t ;
typedef  int /*<<< orphan*/  nstime_t ;

/* Variables and functions */
 int /*<<< orphan*/  nstime_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nstime_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_subtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

uint64_t
timer_usec(const timedelta_t *timer) {
	nstime_t delta;

	nstime_copy(&delta, &timer->t1);
	nstime_subtract(&delta, &timer->t0);
	return nstime_ns(&delta) / 1000;
}