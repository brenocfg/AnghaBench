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
struct hs20_osu_client {int /*<<< orphan*/  ifname; int /*<<< orphan*/  xml; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_snprintf (char*,size_t,char*,char*,...) ; 
 int os_strlen (char*) ; 
 scalar_t__ set_cred (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void set_pps_cred_policy_required_proto_port(struct hs20_osu_client *ctx,
						    int id, xml_node_t *tuple)
{
	xml_node_t *node;
	char *proto, *port;
	char *buf;
	size_t buflen;

	node = get_node(ctx->xml, tuple, "IPProtocol");
	if (node == NULL) {
		wpa_printf(MSG_INFO, "Ignore RequiredProtoPortTuple without mandatory IPProtocol node");
		return;
	}

	proto = xml_node_get_text(ctx->xml, node);
	if (proto == NULL)
		return;

	wpa_printf(MSG_INFO, "- Policy/RequiredProtoPortTuple/<X+>/IPProtocol = %s",
		   proto);

	node = get_node(ctx->xml, tuple, "PortNumber");
	port = node ? xml_node_get_text(ctx->xml, node) : NULL;
	if (port) {
		wpa_printf(MSG_INFO, "- Policy/RequiredProtoPortTuple/<X+>/PortNumber = %s",
			   port);
		buflen = os_strlen(proto) + os_strlen(port) + 10;
		buf = os_malloc(buflen);
		if (buf)
			os_snprintf(buf, buflen, "%s:%s", proto, port);
		xml_node_get_text_free(ctx->xml, port);
	} else {
		buflen = os_strlen(proto) + 10;
		buf = os_malloc(buflen);
		if (buf)
			os_snprintf(buf, buflen, "%s", proto);
	}

	xml_node_get_text_free(ctx->xml, proto);

	if (buf == NULL)
		return;

	if (set_cred(ctx->ifname, id, "req_conn_capab", buf) < 0)
		wpa_printf(MSG_INFO, "Could not set req_conn_capab");

	os_free(buf);
}