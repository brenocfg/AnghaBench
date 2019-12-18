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
typedef  int boolean_t ;

/* Variables and functions */
 int DBGSCR_MDBG_EN ; 
 int cp14_dbgdscrint_get () ; 

__attribute__((used)) static __inline boolean_t
dbg_monitor_is_enabled(void)
{

	return ((cp14_dbgdscrint_get() & DBGSCR_MDBG_EN) != 0);
}