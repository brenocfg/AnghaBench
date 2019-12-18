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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  taskq_t ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  pri_t ;

/* Variables and functions */
 int /*<<< orphan*/ * taskq_create_impl (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

taskq_t *
taskq_create_proc(const char *name, int nthreads, pri_t pri, int minalloc,
    int maxalloc, proc_t *proc, uint_t flags)
{
	return (taskq_create_impl(name, nthreads, pri, proc, flags));
}