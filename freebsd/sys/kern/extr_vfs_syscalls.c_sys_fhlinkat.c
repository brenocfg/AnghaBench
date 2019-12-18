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
struct fhlinkat_args {int /*<<< orphan*/  fhp; int /*<<< orphan*/  to; int /*<<< orphan*/  tofd; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_fhlinkat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_fhlinkat(struct thread *td, struct fhlinkat_args *uap)
{

	return (kern_fhlinkat(td, uap->tofd, uap->to, UIO_USERSPACE, uap->fhp));
}