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
struct aio_fsync_args {int /*<<< orphan*/  aiocbp; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  aiocb_ops ; 
 int kern_aio_fsync (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
sys_aio_fsync(struct thread *td, struct aio_fsync_args *uap)
{

	return (kern_aio_fsync(td, uap->op, uap->aiocbp, &aiocb_ops));
}