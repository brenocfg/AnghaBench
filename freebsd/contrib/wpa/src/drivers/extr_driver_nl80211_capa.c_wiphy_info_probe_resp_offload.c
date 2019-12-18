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
typedef  int /*<<< orphan*/  u32 ;
struct wpa_driver_capa {int /*<<< orphan*/  probe_resp_offloads; int /*<<< orphan*/  flags; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_PROBE_RESP_OFFLOAD ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  probe_resp_offload_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wiphy_info_probe_resp_offload(struct wpa_driver_capa *capa,
					  struct nlattr *tb)
{
	u32 protocols;

	if (tb == NULL)
		return;

	protocols = nla_get_u32(tb);
	wpa_printf(MSG_DEBUG, "nl80211: Supports Probe Response offload in AP "
		   "mode");
	capa->flags |= WPA_DRIVER_FLAGS_PROBE_RESP_OFFLOAD;
	capa->probe_resp_offloads = probe_resp_offload_support(protocols);
}