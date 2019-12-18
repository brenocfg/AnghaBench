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
typedef  size_t uint32_t ;
typedef  size_t uint ;
struct wlan_iface {size_t* wname; } ;
struct asn_oid {size_t len; size_t* subs; } ;

/* Variables and functions */
 size_t strlen (size_t*) ; 

__attribute__((used)) static void
wlan_append_ifindex(struct asn_oid *oid, uint sub, const struct wlan_iface *w)
{
	uint32_t i;

	oid->len = sub + strlen(w->wname) + 1;
	oid->subs[sub] = strlen(w->wname);
	for (i = 1; i <= strlen(w->wname); i++)
		oid->subs[sub + i] = w->wname[i - 1];
}