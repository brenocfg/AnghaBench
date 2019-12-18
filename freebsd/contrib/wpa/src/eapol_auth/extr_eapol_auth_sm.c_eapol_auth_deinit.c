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
struct eapol_authenticator {struct eapol_authenticator* default_wep_key; int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_auth_conf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct eapol_authenticator*) ; 

void eapol_auth_deinit(struct eapol_authenticator *eapol)
{
	if (eapol == NULL)
		return;

	eapol_auth_conf_free(&eapol->conf);
	os_free(eapol->default_wep_key);
	os_free(eapol);
}