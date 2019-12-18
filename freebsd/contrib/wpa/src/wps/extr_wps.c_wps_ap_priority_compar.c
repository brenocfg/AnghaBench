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
struct wps_parse_attr {scalar_t__* selected_registrar; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 

int wps_ap_priority_compar(const struct wpabuf *wps_a,
			   const struct wpabuf *wps_b)
{
	struct wps_parse_attr attr;
	int sel_a, sel_b;

	if (wps_a == NULL || wps_parse_msg(wps_a, &attr) < 0)
		return 1;
	sel_a = attr.selected_registrar && *attr.selected_registrar != 0;

	if (wps_b == NULL || wps_parse_msg(wps_b, &attr) < 0)
		return -1;
	sel_b = attr.selected_registrar && *attr.selected_registrar != 0;

	if (sel_a && !sel_b)
		return -1;
	if (!sel_a && sel_b)
		return 1;

	return 0;
}