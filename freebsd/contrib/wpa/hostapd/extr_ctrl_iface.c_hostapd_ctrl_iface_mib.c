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
struct hostapd_data {int /*<<< orphan*/  radius_srv; } ;

/* Variables and functions */
 scalar_t__ os_strcmp (char const*,char*) ; 
 int radius_server_get_mib (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int hostapd_ctrl_iface_mib(struct hostapd_data *hapd, char *reply,
				  int reply_size, const char *param)
{
#ifdef RADIUS_SERVER
	if (os_strcmp(param, "radius_server") == 0) {
		return radius_server_get_mib(hapd->radius_srv, reply,
					     reply_size);
	}
#endif /* RADIUS_SERVER */
	return -1;
}