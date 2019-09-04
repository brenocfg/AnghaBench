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
 int /*<<< orphan*/  RANKINGS_FRAME ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 

void Rankings_Cache( void ) {
	trap_R_RegisterShaderNoMip( RANKINGS_FRAME );
}