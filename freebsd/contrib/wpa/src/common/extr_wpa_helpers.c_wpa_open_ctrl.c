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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  os_snprintf (char*,int,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 struct wpa_ctrl* wpa_ctrl_open (char*) ; 
 int /*<<< orphan*/  wpas_ctrl_path ; 

__attribute__((used)) static struct wpa_ctrl * wpa_open_ctrl(const char *ifname)
{
	char buf[128];
	struct wpa_ctrl *ctrl;

	os_snprintf(buf, sizeof(buf), "%s%s", wpas_ctrl_path, ifname);
	ctrl = wpa_ctrl_open(buf);
	if (ctrl == NULL)
		printf("wpa_command: wpa_ctrl_open(%s) failed\n", buf);
	return ctrl;
}