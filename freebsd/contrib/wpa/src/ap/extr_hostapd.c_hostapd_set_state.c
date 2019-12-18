#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {int state; TYPE_2__* conf; } ;
typedef  enum hostapd_iface_state { ____Placeholder_hostapd_iface_state } hostapd_iface_state ;
struct TYPE_4__ {TYPE_1__** bss; } ;
struct TYPE_3__ {char* iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  hostapd_state_text (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hostapd_set_state(struct hostapd_iface *iface, enum hostapd_iface_state s)
{
	wpa_printf(MSG_INFO, "%s: interface state %s->%s",
		   iface->conf ? iface->conf->bss[0]->iface : "N/A",
		   hostapd_state_text(iface->state), hostapd_state_text(s));
	iface->state = s;
}