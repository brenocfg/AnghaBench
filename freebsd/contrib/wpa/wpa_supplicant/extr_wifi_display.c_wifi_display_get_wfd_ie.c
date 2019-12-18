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
struct wpabuf {int dummy; } ;
struct wpa_global {scalar_t__* wfd_subelem; int /*<<< orphan*/ * p2p; } ;

/* Variables and functions */
 int MAX_WFD_SUBELEMS ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 scalar_t__ wpabuf_len (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,scalar_t__) ; 

struct wpabuf * wifi_display_get_wfd_ie(struct wpa_global *global)
{
	struct wpabuf *ie;
	size_t len;
	int i;

	if (global->p2p == NULL)
		return NULL;

	len = 0;
	for (i = 0; i < MAX_WFD_SUBELEMS; i++) {
		if (global->wfd_subelem[i])
			len += wpabuf_len(global->wfd_subelem[i]);
	}

	ie = wpabuf_alloc(len);
	if (ie == NULL)
		return NULL;

	for (i = 0; i < MAX_WFD_SUBELEMS; i++) {
		if (global->wfd_subelem[i])
			wpabuf_put_buf(ie, global->wfd_subelem[i]);
	}

	return ie;
}