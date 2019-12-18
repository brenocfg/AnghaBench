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
struct dup_args {scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDDUP_NORMAL ; 
 int kern_dup (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
sys_dup(struct thread *td, struct dup_args *uap)
{

	return (kern_dup(td, FDDUP_NORMAL, 0, (int)uap->fd, 0));
}