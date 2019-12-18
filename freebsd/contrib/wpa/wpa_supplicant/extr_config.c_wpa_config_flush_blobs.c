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
struct wpa_config_blob {struct wpa_config_blob* next; } ;
struct wpa_config {struct wpa_config_blob* blobs; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_config_free_blob (struct wpa_config_blob*) ; 

void wpa_config_flush_blobs(struct wpa_config *config)
{
#ifndef CONFIG_NO_CONFIG_BLOBS
	struct wpa_config_blob *blob, *prev;

	blob = config->blobs;
	config->blobs = NULL;
	while (blob) {
		prev = blob;
		blob = blob->next;
		wpa_config_free_blob(prev);
	}
#endif /* CONFIG_NO_CONFIG_BLOBS */
}