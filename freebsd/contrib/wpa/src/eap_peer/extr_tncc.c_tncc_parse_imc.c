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
struct tnc_if_imc {int imcID; void* path; struct tnc_if_imc* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int TNC_MAX_IMC_ID ; 
 int /*<<< orphan*/  os_free (struct tnc_if_imc*) ; 
 void* os_strdup (char*) ; 
 struct tnc_if_imc* os_zalloc (int) ; 
 struct tnc_if_imc** tnc_imc ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct tnc_if_imc * tncc_parse_imc(char *start, char *end, int *error)
{
	struct tnc_if_imc *imc;
	char *pos, *pos2;
	int i;

	for (i = 0; i < TNC_MAX_IMC_ID; i++) {
		if (tnc_imc[i] == NULL)
			break;
	}
	if (i >= TNC_MAX_IMC_ID) {
		wpa_printf(MSG_DEBUG, "TNC: Too many IMCs");
		return NULL;
	}

	imc = os_zalloc(sizeof(*imc));
	if (imc == NULL) {
		*error = 1;
		return NULL;
	}

	imc->imcID = i;

	pos = start;
	wpa_printf(MSG_DEBUG, "TNC: Configured IMC: %s", pos);
	if (pos + 1 >= end || *pos != '"') {
		wpa_printf(MSG_ERROR, "TNC: Ignoring invalid IMC line '%s' "
			   "(no starting quotation mark)", start);
		os_free(imc);
		return NULL;
	}

	pos++;
	pos2 = pos;
	while (pos2 < end && *pos2 != '"')
		pos2++;
	if (pos2 >= end) {
		wpa_printf(MSG_ERROR, "TNC: Ignoring invalid IMC line '%s' "
			   "(no ending quotation mark)", start);
		os_free(imc);
		return NULL;
	}
	*pos2 = '\0';
	wpa_printf(MSG_DEBUG, "TNC: Name: '%s'", pos);
	imc->name = os_strdup(pos);

	pos = pos2 + 1;
	if (pos >= end || *pos != ' ') {
		wpa_printf(MSG_ERROR, "TNC: Ignoring invalid IMC line '%s' "
			   "(no space after name)", start);
		os_free(imc->name);
		os_free(imc);
		return NULL;
	}

	pos++;
	wpa_printf(MSG_DEBUG, "TNC: IMC file: '%s'", pos);
	imc->path = os_strdup(pos);
	tnc_imc[imc->imcID] = imc;

	return imc;
}