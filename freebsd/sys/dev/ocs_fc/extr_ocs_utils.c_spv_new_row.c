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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;

/* Variables and functions */
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 void** ocs_malloc (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
**spv_new_row(ocs_os_handle_t os, uint32_t rowcount)
{
	return ocs_malloc(os, sizeof(void*) * rowcount, OCS_M_ZERO | OCS_M_NOWAIT);
}