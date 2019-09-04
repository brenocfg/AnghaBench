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
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_ADJUST_AREA_PORTAL_STATE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void trap_AdjustAreaPortalState( gentity_t *ent, qboolean open ) {
	syscall( G_ADJUST_AREA_PORTAL_STATE, ent, open );
}