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
struct hs20_osu_client {int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  cmd_set_pps (struct hs20_osu_client*,char const*) ; 
 scalar_t__ wpa_command (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void hs20_policy_update_complete(struct hs20_osu_client *ctx,
					const char *pps_fname)
{
	wpa_printf(MSG_INFO, "Policy update completed");

	/*
	 * Update wpa_supplicant credentials and reconnect using updated
	 * information.
	 */
	wpa_printf(MSG_INFO, "Updating wpa_supplicant credentials");
	cmd_set_pps(ctx, pps_fname);

	wpa_printf(MSG_INFO, "Requesting reconnection with updated configuration");
	if (wpa_command(ctx->ifname, "INTERWORKING_SELECT auto") < 0)
		wpa_printf(MSG_ERROR, "Failed to request wpa_supplicant to reconnect");
}