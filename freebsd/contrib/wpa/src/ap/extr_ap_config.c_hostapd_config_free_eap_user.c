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
struct hostapd_eap_user {int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  password_len; int /*<<< orphan*/  password; struct hostapd_eap_user* identity; int /*<<< orphan*/  accept_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_config_free_radius_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct hostapd_eap_user*) ; 

void hostapd_config_free_eap_user(struct hostapd_eap_user *user)
{
	hostapd_config_free_radius_attr(user->accept_attr);
	os_free(user->identity);
	bin_clear_free(user->password, user->password_len);
	bin_clear_free(user->salt, user->salt_len);
	os_free(user);
}