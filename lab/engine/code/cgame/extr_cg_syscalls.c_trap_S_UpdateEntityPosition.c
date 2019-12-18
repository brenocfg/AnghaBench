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
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_S_UPDATEENTITYPOSITION ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ; 

void	trap_S_UpdateEntityPosition( int entityNum, const vec3_t origin ) {
	syscall( CG_S_UPDATEENTITYPOSITION, entityNum, origin );
}