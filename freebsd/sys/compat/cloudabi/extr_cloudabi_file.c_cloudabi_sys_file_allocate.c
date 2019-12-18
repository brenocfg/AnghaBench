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
struct cloudabi_sys_file_allocate_args {int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int kern_posix_fallocate (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_file_allocate(struct thread *td,
    struct cloudabi_sys_file_allocate_args *uap)
{

	return (kern_posix_fallocate(td, uap->fd, uap->offset, uap->len));
}