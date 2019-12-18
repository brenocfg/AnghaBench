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
struct ext_password_data {int dummy; } ;
struct eapol_sm {scalar_t__ eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_sm_set_ext_pw_ctx (scalar_t__,struct ext_password_data*) ; 

void eapol_sm_set_ext_pw_ctx(struct eapol_sm *sm,
			     struct ext_password_data *ext)
{
	if (sm && sm->eap)
		eap_sm_set_ext_pw_ctx(sm->eap, ext);
}