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
struct madvise_args {int /*<<< orphan*/  behav; int /*<<< orphan*/  len; scalar_t__ addr; } ;

/* Variables and functions */
 int kern_madvise (struct thread*,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_madvise(struct thread *td, struct madvise_args *uap)
{

	return (kern_madvise(td, (uintptr_t)uap->addr, uap->len, uap->behav));
}