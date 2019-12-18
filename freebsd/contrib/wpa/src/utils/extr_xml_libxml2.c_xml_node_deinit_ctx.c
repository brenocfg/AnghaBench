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
struct xml_node_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct xml_node_ctx*) ; 
 int /*<<< orphan*/  xmlCleanupParser () ; 
 int /*<<< orphan*/  xmlMemoryDump () ; 
 int /*<<< orphan*/  xmlSchemaCleanupTypes () ; 

void xml_node_deinit_ctx(struct xml_node_ctx *ctx)
{
	xmlSchemaCleanupTypes();
	xmlCleanupParser();
	xmlMemoryDump();
	os_free(ctx);
}