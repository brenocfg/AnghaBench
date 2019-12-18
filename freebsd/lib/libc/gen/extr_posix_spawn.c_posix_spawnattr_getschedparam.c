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
struct sched_param {int dummy; } ;
typedef  TYPE_1__* posix_spawnattr_t ;
struct TYPE_3__ {struct sched_param sa_schedparam; } ;

/* Variables and functions */

int
posix_spawnattr_getschedparam(const posix_spawnattr_t * __restrict sa,
    struct sched_param * __restrict schedparam)
{
	*schedparam = (*sa)->sa_schedparam;
	return (0);
}