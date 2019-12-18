#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct osu_data {size_t friendly_name_count; size_t icon_count; size_t serv_desc_count; char* bssid; char* osu_ssid; char* osu_ssid2; char* osu_nai; char* osu_nai2; char* url; int methods; TYPE_3__* icon; TYPE_4__* friendly_name; TYPE_1__* serv_desc; } ;
struct hs20_osu_client {size_t friendly_name_count; size_t icon_count; int /*<<< orphan*/ * icon_hash; int /*<<< orphan*/ * icon_filename; TYPE_2__* friendly_name; } ;
typedef  int /*<<< orphan*/  fname ;
struct TYPE_8__ {char* text; char* lang; } ;
struct TYPE_7__ {int id; char* filename; int /*<<< orphan*/  mime_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  text; int /*<<< orphan*/  lang; } ;
struct TYPE_5__ {char* lang; char* text; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int cmd_oma_dm_prov (struct hs20_osu_client*,char*) ; 
 int cmd_prov (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (struct osu_data*) ; 
 int hs20_web_browser (char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_readfile (char*,size_t*) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char const*,int,char*) ; 
 scalar_t__ os_strcmp (char*,char const*) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int osu_connect (struct hs20_osu_client*,char*,char*,char*,char*,int,int,char*,char*) ; 
 struct osu_data* parse_osu_providers (char*,size_t*) ; 
 int /*<<< orphan*/  sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write_result (struct hs20_osu_client*,char*) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*,...) ; 

__attribute__((used)) static int cmd_osu_select(struct hs20_osu_client *ctx, const char *dir,
			  int connect, int no_prod_assoc,
			  const char *friendly_name)
{
	char fname[255];
	FILE *f;
	struct osu_data *osu = NULL, *last = NULL;
	size_t osu_count = 0, i, j;
	int ret;

	write_summary(ctx, "OSU provider selection");

	if (dir == NULL) {
		wpa_printf(MSG_INFO, "Missing dir parameter to osu_select");
		return -1;
	}

	snprintf(fname, sizeof(fname), "%s/osu-providers.txt", dir);
	osu = parse_osu_providers(fname, &osu_count);
	if (osu == NULL) {
		wpa_printf(MSG_INFO, "Could not find any OSU providers from %s",
			   fname);
		write_result(ctx, "No OSU providers available");
		return -1;
	}

	if (friendly_name) {
		for (i = 0; i < osu_count; i++) {
			last = &osu[i];
			for (j = 0; j < last->friendly_name_count; j++) {
				if (os_strcmp(last->friendly_name[j].text,
					      friendly_name) == 0)
					break;
			}
			if (j < last->friendly_name_count)
				break;
		}
		if (i == osu_count) {
			wpa_printf(MSG_INFO, "Requested operator friendly name '%s' not found in the list of available providers",
				   friendly_name);
			write_summary(ctx, "Requested operator friendly name '%s' not found in the list of available providers",
				      friendly_name);
			free(osu);
			return -1;
		}

		wpa_printf(MSG_INFO, "OSU Provider selected based on requested operator friendly name '%s'",
			   friendly_name);
		write_summary(ctx, "OSU Provider selected based on requested operator friendly name '%s'",
			      friendly_name);
		ret = i + 1;
		goto selected;
	}

	snprintf(fname, sizeof(fname), "%s/osu-providers.html", dir);
	f = fopen(fname, "w");
	if (f == NULL) {
		wpa_printf(MSG_INFO, "Could not open %s", fname);
		free(osu);
		return -1;
	}

	fprintf(f, "<html><head>"
		"<meta http-equiv=\"Content-type\" content=\"text/html; "
		"charset=utf-8\"<title>Select service operator</title>"
		"</head><body><h1>Select service operator</h1>\n");

	if (osu_count == 0)
		fprintf(f, "No online signup available\n");

	for (i = 0; i < osu_count; i++) {
		last = &osu[i];
#ifdef ANDROID
		fprintf(f, "<p>\n"
			"<a href=\"http://localhost:12345/osu/%d\">"
			"<table><tr><td>", (int) i + 1);
#else /* ANDROID */
		fprintf(f, "<p>\n"
			"<a href=\"osu://%d\">"
			"<table><tr><td>", (int) i + 1);
#endif /* ANDROID */
		for (j = 0; j < last->icon_count; j++) {
			fprintf(f, "<img src=\"osu-icon-%d.%s\">\n",
				last->icon[j].id,
				strcasecmp(last->icon[j].mime_type,
					   "image/png") == 0 ? "png" : "icon");
		}
		fprintf(f, "<td>");
		for (j = 0; j < last->friendly_name_count; j++) {
			fprintf(f, "<small>[%s]</small> %s<br>\n",
				last->friendly_name[j].lang,
				last->friendly_name[j].text);
		}
		fprintf(f, "<tr><td colspan=2>");
		for (j = 0; j < last->serv_desc_count; j++) {
			fprintf(f, "<small>[%s]</small> %s<br>\n",
				last->serv_desc[j].lang,
				last->serv_desc[j].text);
		}
		fprintf(f, "</table></a><br><small>BSSID: %s<br>\n"
			"SSID: %s<br>\n",
			last->bssid, last->osu_ssid);
		if (last->osu_ssid2[0])
			fprintf(f, "SSID2: %s<br>\n", last->osu_ssid2);
		if (last->osu_nai[0])
			fprintf(f, "NAI: %s<br>\n", last->osu_nai);
		if (last->osu_nai2[0])
			fprintf(f, "NAI2: %s<br>\n", last->osu_nai2);
		fprintf(f, "URL: %s<br>\n"
			"methods:%s%s<br>\n"
			"</small></p>\n",
			last->url,
			last->methods & 0x01 ? " OMA-DM" : "",
			last->methods & 0x02 ? " SOAP-XML-SPP" : "");
	}

	fprintf(f, "</body></html>\n");

	fclose(f);

	snprintf(fname, sizeof(fname), "file://%s/osu-providers.html", dir);
	write_summary(ctx, "Start web browser with OSU provider selection page");
	ret = hs20_web_browser(fname);

selected:
	if (ret > 0 && (size_t) ret <= osu_count) {
		char *data;
		size_t data_len;

		wpa_printf(MSG_INFO, "Selected OSU id=%d", ret);
		last = &osu[ret - 1];
		ret = 0;
		wpa_printf(MSG_INFO, "BSSID: %s", last->bssid);
		wpa_printf(MSG_INFO, "SSID: %s", last->osu_ssid);
		if (last->osu_ssid2[0])
			wpa_printf(MSG_INFO, "SSID2: %s", last->osu_ssid2);
		wpa_printf(MSG_INFO, "URL: %s", last->url);
		write_summary(ctx, "Selected OSU provider id=%d BSSID=%s SSID=%s URL=%s",
			      ret, last->bssid, last->osu_ssid, last->url);

		ctx->friendly_name_count = last->friendly_name_count;
		for (j = 0; j < last->friendly_name_count; j++) {
			wpa_printf(MSG_INFO, "FRIENDLY_NAME: [%s]%s",
				   last->friendly_name[j].lang,
				   last->friendly_name[j].text);
			os_strlcpy(ctx->friendly_name[j].lang,
				   last->friendly_name[j].lang,
				   sizeof(ctx->friendly_name[j].lang));
			os_strlcpy(ctx->friendly_name[j].text,
				   last->friendly_name[j].text,
				   sizeof(ctx->friendly_name[j].text));
		}

		ctx->icon_count = last->icon_count;
		for (j = 0; j < last->icon_count; j++) {
			char fname[256];

			os_snprintf(fname, sizeof(fname), "%s/osu-icon-%d.%s",
				    dir, last->icon[j].id,
				    strcasecmp(last->icon[j].mime_type,
					       "image/png") == 0 ?
				    "png" : "icon");
			wpa_printf(MSG_INFO, "ICON: %s (%s)",
				   fname, last->icon[j].filename);
			os_strlcpy(ctx->icon_filename[j],
				   last->icon[j].filename,
				   sizeof(ctx->icon_filename[j]));

			data = os_readfile(fname, &data_len);
			if (data) {
				sha256_vector(1, (const u8 **) &data, &data_len,
					      ctx->icon_hash[j]);
				os_free(data);
			}
		}

		if (connect == 2) {
			if (last->methods & 0x02) {
				wpa_printf(MSG_DEBUG,
					   "Calling cmd_prov from cmd_osu_select");
				ret = cmd_prov(ctx, last->url);
			} else if (last->methods & 0x01) {
				wpa_printf(MSG_DEBUG,
					   "Calling cmd_oma_dm_prov from cmd_osu_select");
				ret = cmd_oma_dm_prov(ctx, last->url);
			} else {
				wpa_printf(MSG_DEBUG,
					   "No supported OSU provisioning method");
				ret = -1;
			}
		} else if (connect) {
			ret = osu_connect(ctx, last->bssid, last->osu_ssid,
					  last->osu_ssid2,
					  last->url, last->methods,
					  no_prod_assoc, last->osu_nai,
					  last->osu_nai2);
		}
	} else
		ret = -1;

	free(osu);

	return ret;
}