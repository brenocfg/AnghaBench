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

struct wpa_cred * wpa_config_get_cred(struct wpa_config *config, int id)
{
	struct wpa_cred *cred;

	cred = config->cred;
	while (cred) {
		if (id == cred->id)
			break;
		cred = cred->next;
	}

	return cred;
}