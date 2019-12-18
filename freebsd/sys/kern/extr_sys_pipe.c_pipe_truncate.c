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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct pipe {int pipe_state; } ;
struct file {struct pipe* f_data; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int (* fo_truncate ) (struct file*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ;} ;

/* Variables and functions */
 int PIPE_NAMED ; 
 int invfo_truncate (struct file*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 int stub1 (struct file*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 TYPE_1__ vnops ; 

__attribute__((used)) static int
pipe_truncate(struct file *fp, off_t length, struct ucred *active_cred,
    struct thread *td)
{
	struct pipe *cpipe;
	int error;

	cpipe = fp->f_data;
	if (cpipe->pipe_state & PIPE_NAMED)
		error = vnops.fo_truncate(fp, length, active_cred, td);
	else
		error = invfo_truncate(fp, length, active_cred, td);
	return (error);
}