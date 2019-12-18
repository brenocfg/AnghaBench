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
struct sppp {scalar_t__* state; } ;

/* Variables and functions */
 size_t IDX_PAP ; 
 scalar_t__ STATE_CLOSED ; 
 int /*<<< orphan*/  pap ; 
 int /*<<< orphan*/  sppp_cp_change_state (int /*<<< orphan*/ *,struct sppp*,scalar_t__) ; 

__attribute__((used)) static void
sppp_pap_close(struct sppp *sp)
{
	if (sp->state[IDX_PAP] != STATE_CLOSED)
		sppp_cp_change_state(&pap, sp, STATE_CLOSED);
}