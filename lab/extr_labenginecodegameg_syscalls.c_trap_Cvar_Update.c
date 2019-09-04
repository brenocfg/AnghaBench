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
typedef  int /*<<< orphan*/  vmCvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_CVAR_UPDATE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void	trap_Cvar_Update( vmCvar_t *cvar ) {
	syscall( G_CVAR_UPDATE, cvar );
}