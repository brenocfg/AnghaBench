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
struct ieee802_1x_cp_sm {int CP_state; } ;
typedef  enum cp_states { ____Placeholder_cp_states } cp_states ;

/* Variables and functions */
 int /*<<< orphan*/  CP ; 
 int /*<<< orphan*/  SM_STEP_RUN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee802_1x_cp_step_run(struct ieee802_1x_cp_sm *sm)
{
	enum cp_states prev_state;
	int i;

	for (i = 0; i < 100; i++) {
		prev_state = sm->CP_state;
		SM_STEP_RUN(CP);
		if (prev_state == sm->CP_state)
			break;
	}
}