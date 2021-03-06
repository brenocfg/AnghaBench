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
struct msync_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; scalar_t__ addr; } ;

/* Variables and functions */
 int kern_msync (struct thread*,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_msync(struct thread *td, struct msync_args *uap)
{

	return (kern_msync(td, (uintptr_t)uap->addr, uap->len, uap->flags));
}