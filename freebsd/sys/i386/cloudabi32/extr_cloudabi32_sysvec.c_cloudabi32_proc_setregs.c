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
struct image_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TO_PTR (unsigned long) ; 
 int /*<<< orphan*/  cpu_set_user_tls (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_setregs (struct thread*,struct image_params*,unsigned long) ; 

__attribute__((used)) static void
cloudabi32_proc_setregs(struct thread *td, struct image_params *imgp,
    unsigned long stack)
{

	exec_setregs(td, imgp, stack);
	(void)cpu_set_user_tls(td, TO_PTR(stack));
}