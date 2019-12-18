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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int dtrace_malloc_enabled ; 
 scalar_t__ dtrace_malloc_enabled_count ; 

__attribute__((used)) static void
dtmalloc_disable(void *arg, dtrace_id_t id, void *parg)
{
	uint32_t *p = parg;
	*p = 0;
	dtrace_malloc_enabled_count--;
	if (dtrace_malloc_enabled_count == 0)
		dtrace_malloc_enabled = false;
}