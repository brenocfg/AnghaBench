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
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMARTPQI ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 

void os_mem_free(pqisrc_softstate_t *softs,
			char *addr, size_t size)
{
	/* DBG_FUNC("IN\n"); */

	free((void*)addr, M_SMARTPQI);

	/* DBG_FUNC("OUT\n"); */
}