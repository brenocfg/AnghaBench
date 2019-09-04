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
 int /*<<< orphan*/  PASSFLOAT (float) ; 
 int /*<<< orphan*/  UI_R_ADDLIGHTTOSCENE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void trap_R_AddLightToScene( const vec3_t org, float intensity, float r, float g, float b ) {
	syscall( UI_R_ADDLIGHTTOSCENE, org, PASSFLOAT(intensity), PASSFLOAT(r), PASSFLOAT(g), PASSFLOAT(b) );
}