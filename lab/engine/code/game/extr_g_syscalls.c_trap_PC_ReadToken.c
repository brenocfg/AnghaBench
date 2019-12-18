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
typedef  int /*<<< orphan*/  pc_token_t ;

/* Variables and functions */
 int /*<<< orphan*/  BOTLIB_PC_READ_TOKEN ; 
 int syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int trap_PC_ReadToken( int handle, pc_token_t *pc_token ) {
	return syscall( BOTLIB_PC_READ_TOKEN, handle, pc_token );
}