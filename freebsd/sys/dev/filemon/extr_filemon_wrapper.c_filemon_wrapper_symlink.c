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
struct thread {int dummy; } ;
struct symlink_args {int /*<<< orphan*/  link; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  _filemon_wrapper_link (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sys_symlink (struct thread*,struct symlink_args*) ; 

__attribute__((used)) static int
filemon_wrapper_symlink(struct thread *td, struct symlink_args *uap)
{
	int ret;

	if ((ret = sys_symlink(td, uap)) == 0)
		_filemon_wrapper_link(td, uap->path, uap->link);

	return (ret);
}