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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 void* find_node_by_prop_value (int /*<<< orphan*/ *,char*,char*,int) ; 

__attribute__((used)) static inline void *find_node_by_linuxphandle(const u32 linuxphandle)
{
	return find_node_by_prop_value(NULL, "linux,phandle",
			(char *)&linuxphandle, sizeof(u32));
}