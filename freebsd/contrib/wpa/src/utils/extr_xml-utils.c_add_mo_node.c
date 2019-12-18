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
 char* get_node_text (struct xml_node_ctx*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * get_node_uri (struct xml_node_ctx*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  xml_node_create (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * xml_node_create_root (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xml_node_create_text (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  xml_node_get_text_free (struct xml_node_ctx*,char*) ; 
 int /*<<< orphan*/  xml_node_set_text (struct xml_node_ctx*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static xml_node_t * add_mo_node(struct xml_node_ctx *ctx, xml_node_t *root,
				xml_node_t *node, const char *uri)
{
	char *nodename, *value, *path;
	xml_node_t *parent;

	nodename = get_node_text(ctx, node, "NodeName");
	if (nodename == NULL)
		return NULL;
	value = get_node_text(ctx, node, "Value");

	if (root == NULL) {
		root = xml_node_create_root(ctx, NULL, NULL, NULL,
					    nodename);
		if (root && value)
			xml_node_set_text(ctx, root, value);
	} else {
		if (uri == NULL) {
			xml_node_get_text_free(ctx, nodename);
			xml_node_get_text_free(ctx, value);
			return NULL;
		}
		path = get_node_text(ctx, node, "Path");
		if (path)
			uri = path;
		parent = get_node_uri(ctx, root, uri);
		xml_node_get_text_free(ctx, path);
		if (parent == NULL) {
			printf("Could not find URI '%s'\n", uri);
			xml_node_get_text_free(ctx, nodename);
			xml_node_get_text_free(ctx, value);
			return NULL;
		}
		if (value)
			xml_node_create_text(ctx, parent, NULL, nodename,
					     value);
		else
			xml_node_create(ctx, parent, NULL, nodename);
	}

	xml_node_get_text_free(ctx, nodename);
	xml_node_get_text_free(ctx, value);

	return root;
}