#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct wps_registrar {TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int config_methods; } ;

/* Variables and functions */
 int ATTR_CONFIG_METHODS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPS_CONFIG_PHY_PUSHBUTTON ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int WPS_CONFIG_VIRT_PUSHBUTTON ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 

__attribute__((used)) static int wps_build_probe_config_methods(struct wps_registrar *reg,
					  struct wpabuf *msg)
{
	u16 methods;
	/*
	 * These are the methods that the AP supports as an Enrollee for adding
	 * external Registrars.
	 */
	methods = reg->wps->config_methods & ~WPS_CONFIG_PUSHBUTTON;
	methods &= ~(WPS_CONFIG_VIRT_PUSHBUTTON |
		     WPS_CONFIG_PHY_PUSHBUTTON);
	wpa_printf(MSG_DEBUG, "WPS:  * Config Methods (%x)", methods);
	wpabuf_put_be16(msg, ATTR_CONFIG_METHODS);
	wpabuf_put_be16(msg, 2);
	wpabuf_put_be16(msg, methods);
	return 0;
}