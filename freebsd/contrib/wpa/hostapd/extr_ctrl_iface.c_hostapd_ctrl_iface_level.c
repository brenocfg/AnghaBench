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
struct hostapd_data {int /*<<< orphan*/  ctrl_dst; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int ctrl_iface_level (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hostapd_ctrl_iface_level(struct hostapd_data *hapd,
				    struct sockaddr_storage *from,
				    socklen_t fromlen,
				    char *level)
{
	return ctrl_iface_level(&hapd->ctrl_dst, from, fromlen, level);
}