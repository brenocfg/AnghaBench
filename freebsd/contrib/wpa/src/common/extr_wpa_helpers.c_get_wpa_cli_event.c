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
struct wpa_ctrl {int dummy; } ;

/* Variables and functions */
 int get_wpa_cli_event2 (struct wpa_ctrl*,char const*,int /*<<< orphan*/ *,char*,size_t) ; 

int get_wpa_cli_event(struct wpa_ctrl *mon,
		      const char *event, char *buf, size_t buf_size)
{
	return get_wpa_cli_event2(mon, event, NULL, buf, buf_size);
}