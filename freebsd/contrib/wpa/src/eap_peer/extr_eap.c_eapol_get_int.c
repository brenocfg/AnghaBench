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
struct TYPE_2__ {unsigned int (* get_int ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 unsigned int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int eapol_get_int(struct eap_sm *sm, enum eapol_int_var var)
{
	return sm->eapol_cb->get_int(sm->eapol_ctx, var);
}