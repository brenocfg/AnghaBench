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
struct cpuset_setid_args {int /*<<< orphan*/  setid; int /*<<< orphan*/  id; int /*<<< orphan*/  which; } ;

/* Variables and functions */
 int kern_cpuset_setid (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_cpuset_setid(struct thread *td, struct cpuset_setid_args *uap)
{

	return (kern_cpuset_setid(td, uap->which, uap->id, uap->setid));
}