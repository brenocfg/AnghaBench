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
 int /*<<< orphan*/  PF_RULES_WLOCK () ; 
 int /*<<< orphan*/  PF_RULES_WUNLOCK () ; 
 int /*<<< orphan*/  V_pfsync_clear_states_ptr ; 
 int /*<<< orphan*/  V_pfsync_defer_ptr ; 
 int /*<<< orphan*/  V_pfsync_delete_state_ptr ; 
 int /*<<< orphan*/  V_pfsync_insert_state_ptr ; 
 int /*<<< orphan*/  V_pfsync_state_import_ptr ; 
 int /*<<< orphan*/  V_pfsync_update_state_ptr ; 
 int /*<<< orphan*/  pfsync_clear_states ; 
 int /*<<< orphan*/  pfsync_defer ; 
 int /*<<< orphan*/  pfsync_delete_state ; 
 int /*<<< orphan*/  pfsync_insert_state ; 
 int /*<<< orphan*/  pfsync_state_import ; 
 int /*<<< orphan*/  pfsync_update_state ; 

__attribute__((used)) static void
pfsync_pointers_init()
{

	PF_RULES_WLOCK();
	V_pfsync_state_import_ptr = pfsync_state_import;
	V_pfsync_insert_state_ptr = pfsync_insert_state;
	V_pfsync_update_state_ptr = pfsync_update_state;
	V_pfsync_delete_state_ptr = pfsync_delete_state;
	V_pfsync_clear_states_ptr = pfsync_clear_states;
	V_pfsync_defer_ptr = pfsync_defer;
	PF_RULES_WUNLOCK();
}