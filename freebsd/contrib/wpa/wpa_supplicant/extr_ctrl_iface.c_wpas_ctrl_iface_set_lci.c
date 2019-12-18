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
struct wpa_supplicant {struct wpabuf* lci; int /*<<< orphan*/  lci_time; } ;

/* Variables and functions */
 scalar_t__ os_get_reltime (int /*<<< orphan*/ *) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct wpabuf* wpabuf_parse_bin (char const*) ; 

__attribute__((used)) static int wpas_ctrl_iface_set_lci(struct wpa_supplicant *wpa_s,
				   const char *cmd)
{
	struct wpabuf *lci;

	if (*cmd == '\0' || os_strcmp(cmd, "\"\"") == 0) {
		wpabuf_free(wpa_s->lci);
		wpa_s->lci = NULL;
		return 0;
	}

	lci = wpabuf_parse_bin(cmd);
	if (!lci)
		return -1;

	if (os_get_reltime(&wpa_s->lci_time)) {
		wpabuf_free(lci);
		return -1;
	}

	wpabuf_free(wpa_s->lci);
	wpa_s->lci = lci;

	return 0;
}