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
typedef  struct wpa_config_blob {struct wpa_config_blob const* next; int /*<<< orphan*/  name; } const wpa_config_blob ;
struct wpa_config {struct wpa_config_blob const* blobs; } ;

/* Variables and functions */
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char const*) ; 

const struct wpa_config_blob * wpa_config_get_blob(struct wpa_config *config,
						   const char *name)
{
	struct wpa_config_blob *blob = config->blobs;

	while (blob) {
		if (os_strcmp(blob->name, name) == 0)
			return blob;
		blob = blob->next;
	}
	return NULL;
}