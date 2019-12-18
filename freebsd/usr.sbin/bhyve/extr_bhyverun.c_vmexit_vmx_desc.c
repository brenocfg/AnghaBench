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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t nitems (char const**) ; 
 char const** vmx_exit_reason_desc ; 

__attribute__((used)) static const char *
vmexit_vmx_desc(uint32_t exit_reason)
{

	if (exit_reason >= nitems(vmx_exit_reason_desc) ||
	    vmx_exit_reason_desc[exit_reason] == NULL)
		return ("Unknown");
	return (vmx_exit_reason_desc[exit_reason]);
}