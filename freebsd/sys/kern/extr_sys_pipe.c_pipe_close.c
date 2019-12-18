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
struct thread {int dummy; } ;
struct file {int /*<<< orphan*/ * f_data; int /*<<< orphan*/ * f_ops; int /*<<< orphan*/ * f_vnode; } ;
struct TYPE_2__ {int (* fo_close ) (struct file*,struct thread*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  badfileops ; 
 int /*<<< orphan*/  pipe_dtor (int /*<<< orphan*/ *) ; 
 int stub1 (struct file*,struct thread*) ; 
 TYPE_1__ vnops ; 

__attribute__((used)) static int
pipe_close(struct file *fp, struct thread *td)
{

	if (fp->f_vnode != NULL) 
		return vnops.fo_close(fp, td);
	fp->f_ops = &badfileops;
	pipe_dtor(fp->f_data);
	fp->f_data = NULL;
	return (0);
}