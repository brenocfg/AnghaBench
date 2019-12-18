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

/* Variables and functions */
 int /*<<< orphan*/  BOTLIB_AAS_VALUE_FOR_BSP_EPAIR_KEY ; 
 int syscall (int /*<<< orphan*/ ,int,char*,char*,int) ; 

int trap_AAS_ValueForBSPEpairKey(int ent, char *key, char *value, int size) {
	return syscall( BOTLIB_AAS_VALUE_FOR_BSP_EPAIR_KEY, ent, key, value, size );
}