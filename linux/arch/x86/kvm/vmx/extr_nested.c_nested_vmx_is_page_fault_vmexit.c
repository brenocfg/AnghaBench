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
typedef  int u16 ;
struct vmcs12 {unsigned int exception_bitmap; int page_fault_error_code_mask; int page_fault_error_code_match; } ;

/* Variables and functions */
 unsigned int PF_VECTOR ; 

__attribute__((used)) static bool nested_vmx_is_page_fault_vmexit(struct vmcs12 *vmcs12,
					    u16 error_code)
{
	bool inequality, bit;

	bit = (vmcs12->exception_bitmap & (1u << PF_VECTOR)) != 0;
	inequality =
		(error_code & vmcs12->page_fault_error_code_mask) !=
		 vmcs12->page_fault_error_code_match;
	return inequality ^ bit;
}