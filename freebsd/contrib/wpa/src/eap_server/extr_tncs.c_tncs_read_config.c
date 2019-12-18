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
struct tncs_global {struct tnc_if_imv* imv; } ;
struct tnc_if_imv {struct tnc_if_imv* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  TNC_CONFIG_FILE ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_readfile (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 struct tnc_if_imv* tncs_parse_imv (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tncs_read_config(struct tncs_global *global)
{
	char *config, *end, *pos, *line_end;
	size_t config_len;
	struct tnc_if_imv *imv, *last;
	int id = 0;

	last = NULL;

	config = os_readfile(TNC_CONFIG_FILE, &config_len);
	if (config == NULL) {
		wpa_printf(MSG_ERROR, "TNC: Could not open TNC configuration "
			   "file '%s'", TNC_CONFIG_FILE);
		return -1;
	}

	end = config + config_len;
	for (pos = config; pos < end; pos = line_end + 1) {
		line_end = pos;
		while (*line_end != '\n' && *line_end != '\r' &&
		       line_end < end)
			line_end++;
		*line_end = '\0';

		if (os_strncmp(pos, "IMV ", 4) == 0) {
			int error = 0;

			imv = tncs_parse_imv(id++, pos + 4, line_end, &error);
			if (error)
				return -1;
			if (imv) {
				if (last == NULL)
					global->imv = imv;
				else
					last->next = imv;
				last = imv;
			}
		}
	}

	os_free(config);

	return 0;
}