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
struct hs20_osu_client {int /*<<< orphan*/  xml; int /*<<< orphan*/  fqdn; scalar_t__ client_cert_present; } ;
typedef  int /*<<< orphan*/  backup ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * get_child_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ os_file_exists (char*) ; 
 scalar_t__ process_est_cert (struct hs20_osu_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rename (char const*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* xml_node_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int update_pps_file(struct hs20_osu_client *ctx, const char *pps_fname,
		    xml_node_t *pps)
{
	char *str;
	FILE *f;
	char backup[300];

	if (ctx->client_cert_present) {
		xml_node_t *cert;
		cert = get_child_node(ctx->xml, pps,
				      "Credential/DigitalCertificate/"
				      "CertSHA256Fingerprint");
		if (cert && os_file_exists("Cert/est_cert.der") &&
		    process_est_cert(ctx, cert, ctx->fqdn) < 0) {
			wpa_printf(MSG_INFO, "EST certificate update processing failed on PPS MO update");
			return -1;
		}
	}

	wpa_printf(MSG_INFO, "Updating PPS MO %s", pps_fname);

	str = xml_node_to_str(ctx->xml, pps);
	if (str == NULL) {
		wpa_printf(MSG_ERROR, "No node found");
		return -1;
	}
	wpa_printf(MSG_MSGDUMP, "[hs20] Updated PPS: '%s'", str);

	snprintf(backup, sizeof(backup), "%s.bak", pps_fname);
	rename(pps_fname, backup);
	f = fopen(pps_fname, "w");
	if (f == NULL) {
		wpa_printf(MSG_INFO, "Could not write PPS");
		rename(backup, pps_fname);
		free(str);
		return -1;
	}
	fprintf(f, "%s\n", str);
	fclose(f);

	free(str);

	return 0;
}