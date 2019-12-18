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
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_ddfname (struct xml_node_ctx*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  node_to_tnds (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * xml_node_create (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * xml_node_create_root (struct xml_node_ctx*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_create_text (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  xml_node_free (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 
 char* xml_node_get_localname (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 

xml_node_t * mo_to_tnds(struct xml_node_ctx *ctx, xml_node_t *mo,
			int use_path, const char *urn, const char *ns_uri)
{
	xml_node_t *root;
	xml_node_t *node;
	const char *name;

	root = xml_node_create_root(ctx, ns_uri, NULL, NULL, "MgmtTree");
	if (root == NULL)
		return NULL;

	xml_node_create_text(ctx, root, NULL, "VerDTD", "1.2");

	name = xml_node_get_localname(ctx, mo);

	node = xml_node_create(ctx, root, NULL, "Node");
	if (node == NULL)
		goto fail;
	xml_node_create_text(ctx, node, NULL, "NodeName", name);
	if (urn)
		add_ddfname(ctx, node, urn);

	node_to_tnds(ctx, use_path ? root : node, mo, use_path ? name : NULL);

	return root;

fail:
	xml_node_free(ctx, root);
	return NULL;
}