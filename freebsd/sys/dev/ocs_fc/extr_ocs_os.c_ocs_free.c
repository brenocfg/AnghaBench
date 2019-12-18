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
typedef  int /*<<< orphan*/  ocs_os_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_OCS ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,void*,size_t) ; 

void
ocs_free(ocs_os_handle_t os, void *addr, size_t size)
{
#ifndef OCS_DEBUG_MEMORY
	free(addr, M_OCS);
#else
	printf("F: %p %ld\n", addr, size);
	free(addr, M_OCS);
#endif
}