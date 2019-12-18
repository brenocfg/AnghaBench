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
struct chdir_args {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_chdir (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_chdir(struct thread *td, struct chdir_args *uap)
{

	return (kern_chdir(td, uap->path, UIO_USERSPACE));
}