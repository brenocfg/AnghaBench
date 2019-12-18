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
struct tnc_if_imv {int imvID; void* path; void* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int TNC_MAX_IMV_ID ; 
 int /*<<< orphan*/  os_free (struct tnc_if_imv*) ; 
 void* os_strdup (char*) ; 
 struct tnc_if_imv* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct tnc_if_imv * tncs_parse_imv(int id, char *start, char *end,
					  int *error)
{
	struct tnc_if_imv *imv;
	char *pos, *pos2;

	if (id >= TNC_MAX_IMV_ID) {
		wpa_printf(MSG_DEBUG, "TNC: Too many IMVs");
		return NULL;
	}

	imv = os_zalloc(sizeof(*imv));
	if (imv == NULL) {
		*error = 1;
		return NULL;
	}

	imv->imvID = id;

	pos = start;
	wpa_printf(MSG_DEBUG, "TNC: Configured IMV: %s", pos);
	if (pos + 1 >= end || *pos != '"') {
		wpa_printf(MSG_ERROR, "TNC: Ignoring invalid IMV line '%s' "
			   "(no starting quotation mark)", start);
		os_free(imv);
		return NULL;
	}

	pos++;
	pos2 = pos;
	while (pos2 < end && *pos2 != '"')
		pos2++;
	if (pos2 >= end) {
		wpa_printf(MSG_ERROR, "TNC: Ignoring invalid IMV line '%s' "
			   "(no ending quotation mark)", start);
		os_free(imv);
		return NULL;
	}
	*pos2 = '\0';
	wpa_printf(MSG_DEBUG, "TNC: Name: '%s'", pos);
	imv->name = os_strdup(pos);

	pos = pos2 + 1;
	if (pos >= end || *pos != ' ') {
		wpa_printf(MSG_ERROR, "TNC: Ignoring invalid IMV line '%s' "
			   "(no space after name)", start);
		os_free(imv);
		return NULL;
	}

	pos++;
	wpa_printf(MSG_DEBUG, "TNC: IMV file: '%s'", pos);
	imv->path = os_strdup(pos);

	return imv;
}