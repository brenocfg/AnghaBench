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
struct task_struct {int dummy; } ;
struct TYPE_2__ {unsigned long buf_size; } ;
typedef  TYPE_1__ pfm_default_smpl_arg_t ;

/* Variables and functions */

__attribute__((used)) static int
default_get_size(struct task_struct *task, unsigned int flags, int cpu, void *data, unsigned long *size)
{
	pfm_default_smpl_arg_t *arg = (pfm_default_smpl_arg_t *)data;

	/*
	 * size has been validated in default_validate
	 */
	*size = arg->buf_size;

	return 0;
}