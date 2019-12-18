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
struct eapol_sm {unsigned int idleWhile; } ;
typedef  enum eapol_int_var { ____Placeholder_eapol_int_var } eapol_int_var ;

/* Variables and functions */
#define  EAPOL_idleWhile 128 
 int /*<<< orphan*/  eapol_enable_timer_tick (struct eapol_sm*) ; 

__attribute__((used)) static void eapol_sm_set_int(void *ctx, enum eapol_int_var variable,
			     unsigned int value)
{
	struct eapol_sm *sm = ctx;
	if (sm == NULL)
		return;
	switch (variable) {
	case EAPOL_idleWhile:
		sm->idleWhile = value;
		if (sm->idleWhile > 0)
			eapol_enable_timer_tick(sm);
		break;
	}
}