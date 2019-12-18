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
 int /*<<< orphan*/ * get_node_iter (struct xml_node_ctx*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (char const*) ; 

xml_node_t * get_node(struct xml_node_ctx *ctx, xml_node_t *root,
		      const char *path)
{
	char *search;
	xml_node_t *node;

	search = os_strdup(path);
	if (search == NULL)
		return NULL;

	node = get_node_iter(ctx, root, search);

	os_free(search);
	return node;
}