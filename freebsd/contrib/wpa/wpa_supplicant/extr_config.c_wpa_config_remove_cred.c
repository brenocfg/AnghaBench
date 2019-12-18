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
struct wpa_cred {int id; struct wpa_cred* next; } ;
struct wpa_config {struct wpa_cred* cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_config_free_cred (struct wpa_cred*) ; 

int wpa_config_remove_cred(struct wpa_config *config, int id)
{
	struct wpa_cred *cred, *prev = NULL;

	cred = config->cred;
	while (cred) {
		if (id == cred->id)
			break;
		prev = cred;
		cred = cred->next;
	}

	if (cred == NULL)
		return -1;

	if (prev)
		prev->next = cred->next;
	else
		config->cred = cred->next;

	wpa_config_free_cred(cred);
	return 0;
}