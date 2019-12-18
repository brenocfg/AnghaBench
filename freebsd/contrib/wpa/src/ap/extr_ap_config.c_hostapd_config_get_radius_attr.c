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
typedef  scalar_t__ u8 ;
struct hostapd_radius_attr {scalar_t__ type; struct hostapd_radius_attr* next; } ;

/* Variables and functions */

struct hostapd_radius_attr *
hostapd_config_get_radius_attr(struct hostapd_radius_attr *attr, u8 type)
{
	for (; attr; attr = attr->next) {
		if (attr->type == type)
			return attr;
	}
	return NULL;
}