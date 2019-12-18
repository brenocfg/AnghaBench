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
struct linux_sethostname_args {int /*<<< orphan*/  len; int /*<<< orphan*/  hostname; } ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_HOSTNAME ; 
 int userland_sysctl (struct thread*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_sethostname(struct thread *td, struct linux_sethostname_args *args)
{
	int name[2];

	name[0] = CTL_KERN;
	name[1] = KERN_HOSTNAME;
	return (userland_sysctl(td, name, 2, 0, 0, 0, args->hostname,
	    args->len, 0, 0));
}