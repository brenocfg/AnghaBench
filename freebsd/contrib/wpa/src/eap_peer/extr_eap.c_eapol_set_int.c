#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eap_sm {int /*<<< orphan*/  eapol_ctx; TYPE_1__* eapol_cb; } ;
typedef  enum eapol_int_var { ____Placeholder_eapol_int_var } eapol_int_var ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_int ) (int /*<<< orphan*/ ,int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void eapol_set_int(struct eap_sm *sm, enum eapol_int_var var,
			  unsigned int value)
{
	sm->eapol_cb->set_int(sm->eapol_ctx, var, value);
}