#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct pthread {TYPE_1__* wake_addr; } ;
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int _thr_umtx_timedwait_uint (scalar_t__*,int /*<<< orphan*/ ,int,struct timespec const*,int /*<<< orphan*/ ) ; 

int
_thr_sleep(struct pthread *curthread, int clockid,
	const struct timespec *abstime)
{

	if (curthread->wake_addr->value != 0)
		return (0);

	return _thr_umtx_timedwait_uint(&curthread->wake_addr->value, 0,
                 clockid, abstime, 0);
}