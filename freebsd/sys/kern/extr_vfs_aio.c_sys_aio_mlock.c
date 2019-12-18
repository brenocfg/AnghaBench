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
struct aio_mlock_args {int /*<<< orphan*/  aiocbp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_MLOCK ; 
 int aio_aqueue (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aiocb_ops ; 

int
sys_aio_mlock(struct thread *td, struct aio_mlock_args *uap)
{

	return (aio_aqueue(td, uap->aiocbp, NULL, LIO_MLOCK, &aiocb_ops));
}