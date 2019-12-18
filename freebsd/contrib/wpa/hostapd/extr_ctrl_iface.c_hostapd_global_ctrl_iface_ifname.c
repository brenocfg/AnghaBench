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
struct sockaddr_storage {int dummy; } ;
struct hostapd_data {int dummy; } ;
struct hapd_interfaces {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int hostapd_ctrl_iface_receive_process (struct hostapd_data*,char*,char*,int,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 struct hostapd_data* hostapd_interfaces_get_hapd (struct hapd_interfaces*,char const*) ; 
 int os_snprintf (char*,int,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

__attribute__((used)) static int hostapd_global_ctrl_iface_ifname(struct hapd_interfaces *interfaces,
					    const char *ifname,
					    char *buf, char *reply,
					    int reply_size,
					    struct sockaddr_storage *from,
					    socklen_t fromlen)
{
	struct hostapd_data *hapd;

	hapd = hostapd_interfaces_get_hapd(interfaces, ifname);
	if (hapd == NULL) {
		int res;

		res = os_snprintf(reply, reply_size, "FAIL-NO-IFNAME-MATCH\n");
		if (os_snprintf_error(reply_size, res))
			return -1;
		return res;
	}

	return hostapd_ctrl_iface_receive_process(hapd, buf, reply,reply_size,
						  from, fromlen);
}