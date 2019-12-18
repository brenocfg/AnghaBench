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
typedef  int s32 ;
typedef  scalar_t__ phandle ;

/* Variables and functions */
 scalar_t__ __prom_getsibling (scalar_t__) ; 

phandle prom_getsibling(phandle node)
{
	phandle sibnode;

	if ((s32)node == -1)
		return 0;
	sibnode = __prom_getsibling(node);
	if ((s32)sibnode == -1)
		return 0;

	return sibnode;
}