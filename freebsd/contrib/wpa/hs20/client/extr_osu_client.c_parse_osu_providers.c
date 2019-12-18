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
struct osu_lang_text {int /*<<< orphan*/  text; int /*<<< orphan*/  lang; } ;
struct osu_icon {int /*<<< orphan*/  filename; int /*<<< orphan*/  mime_type; int /*<<< orphan*/  lang; int /*<<< orphan*/  id; } ;
struct osu_data {scalar_t__ friendly_name_count; scalar_t__ serv_desc_count; scalar_t__ icon_count; struct osu_icon* icon; struct osu_lang_text* serv_desc; struct osu_lang_text* friendly_name; int /*<<< orphan*/  osu_nai2; int /*<<< orphan*/  osu_nai; int /*<<< orphan*/  osu_ssid2; int /*<<< orphan*/  osu_ssid; int /*<<< orphan*/  methods; int /*<<< orphan*/  url; int /*<<< orphan*/  bssid; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MAX_OSU_VALS ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  memset (struct osu_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 struct osu_data* realloc (struct osu_data*,size_t) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static struct osu_data * parse_osu_providers(const char *fname, size_t *count)
{
	FILE *f;
	char buf[1000];
	struct osu_data *osu = NULL, *last = NULL;
	size_t osu_count = 0;
	char *pos, *end;

	f = fopen(fname, "r");
	if (f == NULL) {
		wpa_printf(MSG_ERROR, "Could not open %s", fname);
		return NULL;
	}

	while (fgets(buf, sizeof(buf), f)) {
		pos = strchr(buf, '\n');
		if (pos)
			*pos = '\0';

		if (strncmp(buf, "OSU-PROVIDER ", 13) == 0) {
			last = realloc(osu, (osu_count + 1) * sizeof(*osu));
			if (last == NULL)
				break;
			osu = last;
			last = &osu[osu_count++];
			memset(last, 0, sizeof(*last));
			snprintf(last->bssid, sizeof(last->bssid), "%s",
				 buf + 13);
			continue;
		}
		if (!last)
			continue;

		if (strncmp(buf, "uri=", 4) == 0) {
			snprintf(last->url, sizeof(last->url), "%s", buf + 4);
			continue;
		}

		if (strncmp(buf, "methods=", 8) == 0) {
			last->methods = strtol(buf + 8, NULL, 16);
			continue;
		}

		if (strncmp(buf, "osu_ssid=", 9) == 0) {
			snprintf(last->osu_ssid, sizeof(last->osu_ssid),
				 "%s", buf + 9);
			continue;
		}

		if (strncmp(buf, "osu_ssid2=", 10) == 0) {
			snprintf(last->osu_ssid2, sizeof(last->osu_ssid2),
				 "%s", buf + 10);
			continue;
		}

		if (os_strncmp(buf, "osu_nai=", 8) == 0) {
			os_snprintf(last->osu_nai, sizeof(last->osu_nai),
				    "%s", buf + 8);
			continue;
		}

		if (os_strncmp(buf, "osu_nai2=", 9) == 0) {
			os_snprintf(last->osu_nai2, sizeof(last->osu_nai2),
				    "%s", buf + 9);
			continue;
		}

		if (strncmp(buf, "friendly_name=", 14) == 0) {
			struct osu_lang_text *txt;
			if (last->friendly_name_count == MAX_OSU_VALS)
				continue;
			pos = strchr(buf + 14, ':');
			if (pos == NULL)
				continue;
			*pos++ = '\0';
			txt = &last->friendly_name[last->friendly_name_count++];
			snprintf(txt->lang, sizeof(txt->lang), "%s", buf + 14);
			snprintf(txt->text, sizeof(txt->text), "%s", pos);
		}

		if (strncmp(buf, "desc=", 5) == 0) {
			struct osu_lang_text *txt;
			if (last->serv_desc_count == MAX_OSU_VALS)
				continue;
			pos = strchr(buf + 5, ':');
			if (pos == NULL)
				continue;
			*pos++ = '\0';
			txt = &last->serv_desc[last->serv_desc_count++];
			snprintf(txt->lang, sizeof(txt->lang), "%s", buf + 5);
			snprintf(txt->text, sizeof(txt->text), "%s", pos);
		}

		if (strncmp(buf, "icon=", 5) == 0) {
			struct osu_icon *icon;
			if (last->icon_count == MAX_OSU_VALS)
				continue;
			icon = &last->icon[last->icon_count++];
			icon->id = atoi(buf + 5);
			pos = strchr(buf, ':');
			if (pos == NULL)
				continue;
			pos = strchr(pos + 1, ':');
			if (pos == NULL)
				continue;
			pos = strchr(pos + 1, ':');
			if (pos == NULL)
				continue;
			pos++;
			end = strchr(pos, ':');
			if (!end)
				continue;
			*end = '\0';
			snprintf(icon->lang, sizeof(icon->lang), "%s", pos);
			pos = end + 1;

			end = strchr(pos, ':');
			if (end)
				*end = '\0';
			snprintf(icon->mime_type, sizeof(icon->mime_type),
				 "%s", pos);
			if (!pos)
				continue;
			pos = end + 1;

			end = strchr(pos, ':');
			if (end)
				*end = '\0';
			snprintf(icon->filename, sizeof(icon->filename),
				 "%s", pos);
			continue;
		}
	}

	fclose(f);

	*count = osu_count;
	return osu;
}