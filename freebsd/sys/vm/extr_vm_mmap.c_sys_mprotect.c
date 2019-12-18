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
struct mprotect_args {int /*<<< orphan*/  prot; int /*<<< orphan*/  len; scalar_t__ addr; } ;

/* Variables and functions */
 int kern_mprotect (struct thread*,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_mprotect(struct thread *td, struct mprotect_args *uap)
{

	return (kern_mprotect(td, (uintptr_t)uap->addr, uap->len, uap->prot));
}