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
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 char* xml_node_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void debug_dump_node(struct hs20_osu_client *ctx, const char *title,
		     xml_node_t *node)
{
	char *str = xml_node_to_str(ctx->xml, node);
	wpa_printf(MSG_DEBUG, "[hs20] %s: '%s'", title, str);
	free(str);
}