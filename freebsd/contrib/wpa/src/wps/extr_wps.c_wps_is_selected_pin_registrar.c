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
struct wps_parse_attr {int dummy; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int is_selected_pin_registrar (struct wps_parse_attr*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 

int wps_is_selected_pin_registrar(const struct wpabuf *msg)
{
	struct wps_parse_attr attr;

	if (wps_parse_msg(msg, &attr) < 0)
		return 0;

	return is_selected_pin_registrar(&attr);
}