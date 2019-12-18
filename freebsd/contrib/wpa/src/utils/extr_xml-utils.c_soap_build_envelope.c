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
typedef  int /*<<< orphan*/  xml_namespace_t ;
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xml_node_add_child (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xml_node_create (struct xml_node_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * xml_node_create_root (struct xml_node_ctx*,char*,char*,int /*<<< orphan*/ **,char*) ; 

xml_node_t * soap_build_envelope(struct xml_node_ctx *ctx, xml_node_t *node)
{
	xml_node_t *envelope, *body;
	xml_namespace_t *ns;

	envelope = xml_node_create_root(
		ctx, "http://www.w3.org/2003/05/soap-envelope", "soap12", &ns,
		"Envelope");
	if (envelope == NULL)
		return NULL;
	body = xml_node_create(ctx, envelope, ns, "Body");
	xml_node_add_child(ctx, body, node);
	return envelope;
}