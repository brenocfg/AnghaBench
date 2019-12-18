#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int coloc_intf_auto_report; struct wpabuf* coloc_intf_elems; scalar_t__ coloc_intf_dialog_token; TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ coloc_intf_reporting; } ;

/* Variables and functions */
 int /*<<< orphan*/  wnm_send_coloc_intf_report (struct wpa_supplicant*,scalar_t__,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 

void wnm_set_coloc_intf_elems(struct wpa_supplicant *wpa_s,
			      struct wpabuf *elems)
{
	wpabuf_free(wpa_s->coloc_intf_elems);
	if (elems && wpabuf_len(elems) == 0) {
		wpabuf_free(elems);
		elems = NULL;
	}
	wpa_s->coloc_intf_elems = elems;

	if (wpa_s->conf->coloc_intf_reporting && wpa_s->coloc_intf_elems &&
	    wpa_s->coloc_intf_dialog_token &&
	    (wpa_s->coloc_intf_auto_report == 1 ||
	     wpa_s->coloc_intf_auto_report == 3)) {
		/* TODO: Check that there has not been less than
		 * wpa_s->coloc_intf_timeout * 200 TU from the last report.
		 */
		wnm_send_coloc_intf_report(wpa_s,
					   wpa_s->coloc_intf_dialog_token,
					   wpa_s->coloc_intf_elems);
	}
}