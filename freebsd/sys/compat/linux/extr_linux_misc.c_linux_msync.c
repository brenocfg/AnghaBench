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
struct linux_msync_args {int fl; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int LINUX_MS_SYNC ; 
 int kern_msync (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
linux_msync(struct thread *td, struct linux_msync_args *args)
{

	return (kern_msync(td, args->addr, args->len,
	    args->fl & ~LINUX_MS_SYNC));
}