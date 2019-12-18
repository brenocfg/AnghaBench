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
struct hs20_osu_client {char* fqdn; char const* ca_fname; int /*<<< orphan*/  xml; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  pps_fname_buf ;
typedef  int /*<<< orphan*/  client_key_buf ;
typedef  int /*<<< orphan*/  client_cert_buf ;
typedef  int /*<<< orphan*/  ca_fname_buf ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * get_child_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_user_pw (struct hs20_osu_client*,int /*<<< orphan*/ *,char*,char**,char**) ; 
 scalar_t__ get_wpa_status (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/ * node_from_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  oma_dm_pol_upd (struct hs20_osu_client*,char const*,char const*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_file_exists (char const*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int os_snprintf (char*,int,char*,char const*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 void* os_strdup (char*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  spp_pol_upd (struct hs20_osu_client*,char const*,char const*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str_clear_free (char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xml_node_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* xml_node_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_node_get_text_free (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cmd_pol_upd(struct hs20_osu_client *ctx, const char *address,
		       const char *pps_fname, const char *ca_fname)
{
	xml_node_t *pps;
	xml_node_t *node;
	char pps_fname_buf[300];
	char ca_fname_buf[200];
	char *uri = NULL;
	char *cred_username = NULL;
	char *cred_password = NULL;
	char client_cert_buf[200];
	char *client_cert = NULL;
	char client_key_buf[200];
	char *client_key = NULL;
	int spp;

	wpa_printf(MSG_INFO, "Policy update requested");

	if (!pps_fname) {
		char buf[256];
		int res;

		wpa_printf(MSG_INFO, "Determining PPS file based on Home SP information");
		if (address && os_strncmp(address, "fqdn=", 5) == 0) {
			wpa_printf(MSG_INFO, "Use requested FQDN from command line");
			os_snprintf(buf, sizeof(buf), "%s", address + 5);
			address = NULL;
		} else if (get_wpa_status(ctx->ifname, "provisioning_sp", buf,
					  sizeof(buf)) < 0) {
			wpa_printf(MSG_INFO, "Could not get provisioning Home SP FQDN from wpa_supplicant");
			return -1;
		}
		os_free(ctx->fqdn);
		ctx->fqdn = os_strdup(buf);
		if (ctx->fqdn == NULL)
			return -1;
		wpa_printf(MSG_INFO, "Home SP FQDN for current credential: %s",
			   buf);
		os_snprintf(pps_fname_buf, sizeof(pps_fname_buf),
			    "SP/%s/pps.xml", ctx->fqdn);
		pps_fname = pps_fname_buf;

		res = os_snprintf(ca_fname_buf, sizeof(ca_fname_buf),
				  "SP/%s/ca.pem", buf);
		if (os_snprintf_error(sizeof(ca_fname_buf), res)) {
			os_free(ctx->fqdn);
			ctx->fqdn = NULL;
			return -1;
		}
		ca_fname = ca_fname_buf;
	}

	if (!os_file_exists(pps_fname)) {
		wpa_printf(MSG_INFO, "PPS file '%s' does not exist or is not accessible",
			   pps_fname);
		return -1;
	}
	wpa_printf(MSG_INFO, "Using PPS file: %s", pps_fname);

	if (ca_fname && !os_file_exists(ca_fname)) {
		wpa_printf(MSG_INFO, "CA file '%s' does not exist or is not accessible",
			   ca_fname);
		return -1;
	}
	wpa_printf(MSG_INFO, "Using server trust root: %s", ca_fname);
	ctx->ca_fname = ca_fname;

	pps = node_from_file(ctx->xml, pps_fname);
	if (pps == NULL) {
		wpa_printf(MSG_INFO, "Could not read PPS MO");
		return -1;
	}

	if (!ctx->fqdn) {
		char *tmp;
		node = get_child_node(ctx->xml, pps, "HomeSP/FQDN");
		if (node == NULL) {
			wpa_printf(MSG_INFO, "No HomeSP/FQDN found from PPS");
			return -1;
		}
		tmp = xml_node_get_text(ctx->xml, node);
		if (tmp == NULL) {
			wpa_printf(MSG_INFO, "No HomeSP/FQDN text found from PPS");
			return -1;
		}
		ctx->fqdn = os_strdup(tmp);
		xml_node_get_text_free(ctx->xml, tmp);
		if (!ctx->fqdn) {
			wpa_printf(MSG_INFO, "No FQDN known");
			return -1;
		}
	}

	node = get_child_node(ctx->xml, pps,
			      "Policy/PolicyUpdate/UpdateMethod");
	if (node) {
		char *tmp;
		tmp = xml_node_get_text(ctx->xml, node);
		if (tmp && os_strcasecmp(tmp, "OMA-DM-ClientInitiated") == 0)
			spp = 0;
		else
			spp = 1;
	} else {
		wpa_printf(MSG_INFO, "No UpdateMethod specified - assume SPP");
		spp = 1;
	}

	get_user_pw(ctx, pps, "Policy/PolicyUpdate/UsernamePassword",
		    &cred_username, &cred_password);
	if (cred_username)
		wpa_printf(MSG_INFO, "Using username: %s", cred_username);
	if (cred_password)
		wpa_printf(MSG_DEBUG, "Using password: %s", cred_password);

	if (cred_username == NULL && cred_password == NULL &&
	    get_child_node(ctx->xml, pps, "Credential/DigitalCertificate")) {
		wpa_printf(MSG_INFO, "Using client certificate");
		os_snprintf(client_cert_buf, sizeof(client_cert_buf),
			    "SP/%s/client-cert.pem", ctx->fqdn);
		client_cert = client_cert_buf;
		os_snprintf(client_key_buf, sizeof(client_key_buf),
			    "SP/%s/client-key.pem", ctx->fqdn);
		client_key = client_key_buf;
	}

	if (!address) {
		node = get_child_node(ctx->xml, pps, "Policy/PolicyUpdate/URI");
		if (node) {
			uri = xml_node_get_text(ctx->xml, node);
			wpa_printf(MSG_INFO, "URI based on PPS: %s", uri);
			address = uri;
		}
	}
	if (!address) {
		wpa_printf(MSG_INFO, "Server URL not known");
		return -1;
	}

	if (spp)
		spp_pol_upd(ctx, address, pps_fname,
			    client_cert, client_key,
			    cred_username, cred_password, pps);
	else
		oma_dm_pol_upd(ctx, address, pps_fname,
			       client_cert, client_key,
			       cred_username, cred_password, pps);

	xml_node_get_text_free(ctx->xml, uri);
	xml_node_get_text_free(ctx->xml, cred_username);
	str_clear_free(cred_password);
	xml_node_free(ctx->xml, pps);

	return 0;
}