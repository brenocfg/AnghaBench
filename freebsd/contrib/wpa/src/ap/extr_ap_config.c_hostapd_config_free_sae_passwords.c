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
struct sae_password_entry {struct sae_password_entry* identifier; int /*<<< orphan*/  password; struct sae_password_entry* next; } ;
struct hostapd_bss_config {struct sae_password_entry* sae_passwords; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct sae_password_entry*) ; 
 int /*<<< orphan*/  str_clear_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_config_free_sae_passwords(struct hostapd_bss_config *conf)
{
	struct sae_password_entry *pw, *tmp;

	pw = conf->sae_passwords;
	conf->sae_passwords = NULL;
	while (pw) {
		tmp = pw;
		pw = pw->next;
		str_clear_free(tmp->password);
		os_free(tmp->identifier);
		os_free(tmp);
	}
}