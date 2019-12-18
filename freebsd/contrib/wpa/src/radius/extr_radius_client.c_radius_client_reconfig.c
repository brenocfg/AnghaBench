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
struct radius_client_data {struct hostapd_radius_servers* conf; } ;
struct hostapd_radius_servers {int dummy; } ;

/* Variables and functions */

void radius_client_reconfig(struct radius_client_data *radius,
			    struct hostapd_radius_servers *conf)
{
	if (radius)
		radius->conf = conf;
}