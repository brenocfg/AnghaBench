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

/* Variables and functions */
 int /*<<< orphan*/  DM_HS20_POLICY_UPDATE ; 
 int /*<<< orphan*/ * build_oma_dm_1 (struct hs20_osu_client*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xml_node_t * build_oma_dm_1_pol_upd(struct hs20_osu_client *ctx,
					   const char *url, int msgid)
{
	xml_node_t *syncml;

	syncml = build_oma_dm_1(ctx, url, msgid, DM_HS20_POLICY_UPDATE);
	if (syncml)
		debug_dump_node(ctx, "OMA-DM Package 1 (pol upd)", syncml);

	return syncml;
}