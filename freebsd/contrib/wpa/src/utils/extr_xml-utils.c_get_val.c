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
 char* xml_node_get_text (struct xml_node_ctx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char * get_val(struct xml_node_ctx *ctx, xml_node_t *node)
{
	char *val, *pos;

	val = xml_node_get_text(ctx, node);
	if (val == NULL)
		return NULL;
	pos = val;
	while (*pos) {
		if (*pos != ' ' && *pos != '\t' && *pos != '\r' && *pos != '\n')
			return val;
		pos++;
	}

	return NULL;
}