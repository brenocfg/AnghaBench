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
struct linux_renameat_args {int /*<<< orphan*/  newname; int /*<<< orphan*/  newdfd; int /*<<< orphan*/  oldname; int /*<<< orphan*/  olddfd; } ;
struct linux_renameat2_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  newname; int /*<<< orphan*/  newdfd; int /*<<< orphan*/  oldname; int /*<<< orphan*/  olddfd; } ;

/* Variables and functions */
 int linux_renameat2 (struct thread*,struct linux_renameat2_args*) ; 

int
linux_renameat(struct thread *td, struct linux_renameat_args *args)
{
	struct linux_renameat2_args renameat2_args = {
	    .olddfd = args->olddfd,
	    .oldname = args->oldname,
	    .newdfd = args->newdfd,
	    .newname = args->newname,
	    .flags = 0
	};

	return (linux_renameat2(td, &renameat2_args));
}