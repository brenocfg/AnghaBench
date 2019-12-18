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
typedef  int /*<<< orphan*/  xml_node_t ;
struct hs20_osu_client {int dummy; } ;
typedef  int /*<<< orphan*/  fname ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ hs20_add_mo (struct hs20_osu_client*,int /*<<< orphan*/ *,char*,int) ; 
 int hs20_spp_update_response (struct hs20_osu_client*,char const*,char*,char*) ; 
 int /*<<< orphan*/  hs20_sub_rem_complete (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int process_spp_user_input_response(struct hs20_osu_client *ctx,
					   const char *session_id,
					   xml_node_t *add_mo)
{
	int ret;
	char fname[300];

	debug_dump_node(ctx, "addMO", add_mo);

	wpa_printf(MSG_INFO, "Subscription registration completed");

	if (hs20_add_mo(ctx, add_mo, fname, sizeof(fname)) < 0) {
		wpa_printf(MSG_INFO, "Could not add MO");
		ret = hs20_spp_update_response(
			ctx, session_id,
			"Error occurred",
			"MO addition or update failed");
		return 0;
	}

	ret = hs20_spp_update_response(ctx, session_id, "OK", NULL);
	if (ret == 0)
		hs20_sub_rem_complete(ctx, fname);

	return 0;
}