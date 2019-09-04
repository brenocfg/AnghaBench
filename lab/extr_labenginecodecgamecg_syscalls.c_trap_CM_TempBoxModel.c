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
typedef  int /*<<< orphan*/  clipHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_CM_TEMPBOXMODEL ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

clipHandle_t trap_CM_TempBoxModel( const vec3_t mins, const vec3_t maxs ) {
	return syscall( CG_CM_TEMPBOXMODEL, mins, maxs );
}