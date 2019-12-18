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
struct wpa_global {int /*<<< orphan*/ ** wfd_subelem; } ;

/* Variables and functions */
 int MAX_WFD_SUBELEMS ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void wifi_display_deinit(struct wpa_global *global)
{
	int i;
	for (i = 0; i < MAX_WFD_SUBELEMS; i++) {
		wpabuf_free(global->wfd_subelem[i]);
		global->wfd_subelem[i] = NULL;
	}
}