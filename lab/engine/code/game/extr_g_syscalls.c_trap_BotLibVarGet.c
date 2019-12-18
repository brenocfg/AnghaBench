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
 int /*<<< orphan*/  BOTLIB_LIBVAR_GET ; 
 int syscall (int /*<<< orphan*/ ,char*,char*,int) ; 

int trap_BotLibVarGet(char *var_name, char *value, int size) {
	return syscall( BOTLIB_LIBVAR_GET, var_name, value, size );
}