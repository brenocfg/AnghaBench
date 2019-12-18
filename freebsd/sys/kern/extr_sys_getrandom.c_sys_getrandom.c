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
struct getrandom_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int kern_getrandom (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_getrandom(struct thread *td, struct getrandom_args *uap)
{
	return (kern_getrandom(td, uap->buf, uap->buflen, uap->flags));
}