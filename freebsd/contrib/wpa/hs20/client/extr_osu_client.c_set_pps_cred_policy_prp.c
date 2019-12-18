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
typedef  int /*<<< orphan*/  val ;
struct hs20_osu_client {int /*<<< orphan*/  xml; int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int atoi (char*) ; 
 int /*<<< orphan*/ * get_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ set_cred_quoted (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void set_pps_cred_policy_prp(struct hs20_osu_client *ctx, int id,
				    xml_node_t *prp)
{
	xml_node_t *node;
	char *txt = NULL, *pos;
	char *prio, *country_buf = NULL;
	const char *country;
	char val[200];
	int priority;

	node = get_node(ctx->xml, prp, "Priority");
	if (node == NULL)
		return;
	prio = xml_node_get_text(ctx->xml, node);
	if (prio == NULL)
		return;
	wpa_printf(MSG_INFO, "- Policy/PreferredRoamingPartnerList/<X+>/Priority = %s",
		   prio);
	priority = atoi(prio);
	xml_node_get_text_free(ctx->xml, prio);

	node = get_node(ctx->xml, prp, "Country");
	if (node) {
		country_buf = xml_node_get_text(ctx->xml, node);
		if (country_buf == NULL)
			return;
		country = country_buf;
		wpa_printf(MSG_INFO, "- Policy/PreferredRoamingPartnerList/<X+>/Country = %s",
			   country);
	} else {
		country = "*";
	}

	node = get_node(ctx->xml, prp, "FQDN_Match");
	if (node == NULL)
		goto out;
	txt = xml_node_get_text(ctx->xml, node);
	if (txt == NULL)
		goto out;
	wpa_printf(MSG_INFO, "- Policy/PreferredRoamingPartnerList/<X+>/FQDN_Match = %s",
		   txt);
	pos = strrchr(txt, ',');
	if (pos == NULL)
		goto out;
	*pos++ = '\0';

	snprintf(val, sizeof(val), "%s,%d,%d,%s", txt,
		 strcmp(pos, "includeSubdomains") != 0, priority, country);
	if (set_cred_quoted(ctx->ifname, id, "roaming_partner", val) < 0)
		wpa_printf(MSG_INFO, "Failed to set cred roaming_partner");
out:
	xml_node_get_text_free(ctx->xml, country_buf);
	xml_node_get_text_free(ctx->xml, txt);
}