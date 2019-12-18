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
struct kimage {int /*<<< orphan*/  start; int /*<<< orphan*/  head; int /*<<< orphan*/  control_code_page; } ;
typedef  int /*<<< orphan*/  (* relocate_kernel_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  __arch_local_irq_stnsm (int) ; 
 int /*<<< orphan*/  disabled_wait () ; 
 scalar_t__ page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_reset_system () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __do_machine_kexec(void *data)
{
	relocate_kernel_t data_mover;
	struct kimage *image = data;

	s390_reset_system();
	data_mover = (relocate_kernel_t) page_to_phys(image->control_code_page);

	__arch_local_irq_stnsm(0xfb); /* disable DAT - avoid no-execute */
	/* Call the moving routine */
	(*data_mover)(&image->head, image->start);

	/* Die if kexec returns */
	disabled_wait();
}