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
 int /*<<< orphan*/  BOTLIB_AI_LOAD_CHARACTER ; 
 int /*<<< orphan*/  PASSFLOAT (float) ; 
 int syscall (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int trap_BotLoadCharacter(char *charfile, float skill) {
	return syscall( BOTLIB_AI_LOAD_CHARACTER, charfile, PASSFLOAT(skill));
}