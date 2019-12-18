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
struct linkat_args {int /*<<< orphan*/  path2; int /*<<< orphan*/  path1; } ;

/* Variables and functions */
 int /*<<< orphan*/  _filemon_wrapper_link (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sys_linkat (struct thread*,struct linkat_args*) ; 

__attribute__((used)) static int
filemon_wrapper_linkat(struct thread *td, struct linkat_args *uap)
{
	int ret;

	if ((ret = sys_linkat(td, uap)) == 0)
		_filemon_wrapper_link(td, uap->path1, uap->path2);

	return (ret);
}