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
struct kimage {int /*<<< orphan*/  control_code_page; } ;

/* Variables and functions */
 int machine_kexec_alloc_page_tables (struct kimage*) ; 
 int /*<<< orphan*/  machine_kexec_prepare_page_tables (struct kimage*) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_memory_x (unsigned long,int) ; 

int machine_kexec_prepare(struct kimage *image)
{
	int error;

	set_memory_x((unsigned long)page_address(image->control_code_page), 1);
	error = machine_kexec_alloc_page_tables(image);
	if (error)
		return error;
	machine_kexec_prepare_page_tables(image);
	return 0;
}