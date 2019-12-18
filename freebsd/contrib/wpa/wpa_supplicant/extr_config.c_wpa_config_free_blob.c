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
struct wpa_config_blob {int /*<<< orphan*/  len; int /*<<< orphan*/  data; struct wpa_config_blob* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct wpa_config_blob*) ; 

void wpa_config_free_blob(struct wpa_config_blob *blob)
{
	if (blob) {
		os_free(blob->name);
		bin_clear_free(blob->data, blob->len);
		os_free(blob);
	}
}