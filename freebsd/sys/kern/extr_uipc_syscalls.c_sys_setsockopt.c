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
struct setsockopt_args {int /*<<< orphan*/  valsize; int /*<<< orphan*/  val; int /*<<< orphan*/  name; int /*<<< orphan*/  level; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_setsockopt (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_setsockopt(struct thread *td, struct setsockopt_args *uap)
{

	return (kern_setsockopt(td, uap->s, uap->level, uap->name,
	    uap->val, UIO_USERSPACE, uap->valsize));
}