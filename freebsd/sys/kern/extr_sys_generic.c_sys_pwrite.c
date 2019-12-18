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
struct pwrite_args {int /*<<< orphan*/  offset; int /*<<< orphan*/  nbyte; int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int kern_pwrite (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_pwrite(struct thread *td, struct pwrite_args *uap)
{

	return (kern_pwrite(td, uap->fd, uap->buf, uap->nbyte, uap->offset));
}