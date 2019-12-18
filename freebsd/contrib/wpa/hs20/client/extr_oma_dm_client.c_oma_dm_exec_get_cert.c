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
 int DM_RESP_BAD_REQUEST ; 
 int DM_RESP_COMMAND_FAILED ; 
 int DM_RESP_OK ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  debug_dump_node (struct hs20_osu_client*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ os_strcasecmp (char const*,char*) ; 
 int osu_get_certificate (struct hs20_osu_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xml_node_from_buf (int /*<<< orphan*/ ,char*) ; 
 char* xml_node_get_localname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int oma_dm_exec_get_cert(struct hs20_osu_client *ctx, xml_node_t *exec)
{
	xml_node_t *node, *getcert;
	char *data;
	const char *name;
	int res;

	wpa_printf(MSG_INFO, "Client certificate enrollment");
	write_summary(ctx, "Client certificate enrollment");

	node = get_node(ctx->xml, exec, "Item/Data");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "No Data node found");
		return DM_RESP_BAD_REQUEST;
	}

	data = xml_node_get_text(ctx->xml, node);
	if (data == NULL) {
		wpa_printf(MSG_INFO, "Invalid data");
		return DM_RESP_BAD_REQUEST;
	}
	wpa_printf(MSG_INFO, "Data: %s", data);
	getcert = xml_node_from_buf(ctx->xml, data);
	xml_node_get_text_free(ctx->xml, data);

	if (getcert == NULL) {
		wpa_printf(MSG_INFO, "Could not parse Item/Data node contents");
		return DM_RESP_BAD_REQUEST;
	}

	debug_dump_node(ctx, "OMA-DM getCertificate", getcert);

	name = xml_node_get_localname(ctx->xml, getcert);
	if (name == NULL || os_strcasecmp(name, "getCertificate") != 0) {
		wpa_printf(MSG_INFO, "Unexpected getCertificate node name '%s'",
			   name);
		return DM_RESP_BAD_REQUEST;
	}

	res = osu_get_certificate(ctx, getcert);

	xml_node_free(ctx->xml, getcert);

	return res == 0 ? DM_RESP_OK : DM_RESP_COMMAND_FAILED;
}