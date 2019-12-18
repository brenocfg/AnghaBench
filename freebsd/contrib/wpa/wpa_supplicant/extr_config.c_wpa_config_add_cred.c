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
struct wpa_cred {int id; struct wpa_cred* next; int /*<<< orphan*/  sim_num; } ;
struct wpa_config {struct wpa_cred* cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_USER_SELECTED_SIM ; 
 struct wpa_cred* os_zalloc (int) ; 

struct wpa_cred * wpa_config_add_cred(struct wpa_config *config)
{
	int id;
	struct wpa_cred *cred, *last = NULL;

	id = -1;
	cred = config->cred;
	while (cred) {
		if (cred->id > id)
			id = cred->id;
		last = cred;
		cred = cred->next;
	}
	id++;

	cred = os_zalloc(sizeof(*cred));
	if (cred == NULL)
		return NULL;
	cred->id = id;
	cred->sim_num = DEFAULT_USER_SELECTED_SIM;
	if (last)
		last->next = cred;
	else
		config->cred = cred;

	return cred;
}