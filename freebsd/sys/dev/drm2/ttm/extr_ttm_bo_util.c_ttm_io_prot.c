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
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int TTM_PL_FLAG_WC ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 

vm_memattr_t
ttm_io_prot(uint32_t caching_flags)
{
#if defined(__i386__) || defined(__amd64__) || defined(__powerpc__) || 	\
 defined(__arm__)
	if (caching_flags & TTM_PL_FLAG_WC)
		return (VM_MEMATTR_WRITE_COMBINING);
	else
		/*
		 * We do not support i386, look at the linux source
		 * for the reason of the comment.
		 */
		return (VM_MEMATTR_UNCACHEABLE);
#else
#error Port me
#endif
}