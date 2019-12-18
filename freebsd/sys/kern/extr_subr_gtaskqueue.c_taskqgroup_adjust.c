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
struct taskqgroup {int /*<<< orphan*/  tqg_lock; } ;

/* Variables and functions */
 int _taskqgroup_adjust (struct taskqgroup*,int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
taskqgroup_adjust(struct taskqgroup *qgroup, int cnt, int stride)
{
	int error;

	mtx_lock(&qgroup->tqg_lock);
	error = _taskqgroup_adjust(qgroup, cnt, stride);
	mtx_unlock(&qgroup->tqg_lock);

	return (error);
}