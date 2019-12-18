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
struct hs20_osu_client {int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int /*<<< orphan*/ * xml_node_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  xml_node_create_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void oma_dm_add_locuri(struct hs20_osu_client *ctx, xml_node_t *parent,
			      const char *element, const char *uri)
{
	xml_node_t *node;

	node = xml_node_create(ctx->xml, parent, NULL, element);
	if (node == NULL)
		return;
	xml_node_create_text(ctx->xml, node, NULL, "LocURI", uri);
}