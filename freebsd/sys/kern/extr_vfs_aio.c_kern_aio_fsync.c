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
struct aiocb_ops {int dummy; } ;
struct aiocb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LIO_SYNC ; 
 int O_SYNC ; 
 int aio_aqueue (struct thread*,struct aiocb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct aiocb_ops*) ; 

__attribute__((used)) static int
kern_aio_fsync(struct thread *td, int op, struct aiocb *ujob,
    struct aiocb_ops *ops)
{

	if (op != O_SYNC) /* XXX lack of O_DSYNC */
		return (EINVAL);
	return (aio_aqueue(td, ujob, NULL, LIO_SYNC, ops));
}