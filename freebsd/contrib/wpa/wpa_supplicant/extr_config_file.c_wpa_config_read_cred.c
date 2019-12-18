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
struct wpa_cred {int id; int /*<<< orphan*/  sim_num; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_USER_SELECTED_SIM ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 struct wpa_cred* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_config_free_cred (struct wpa_cred*) ; 
 scalar_t__ wpa_config_get_line (char*,int,int /*<<< orphan*/ *,int*,char**) ; 
 scalar_t__ wpa_config_set_cred (struct wpa_cred*,char*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static struct wpa_cred * wpa_config_read_cred(FILE *f, int *line, int id)
{
	struct wpa_cred *cred;
	int errors = 0, end = 0;
	char buf[256], *pos, *pos2;

	wpa_printf(MSG_MSGDUMP, "Line: %d - start of a new cred block", *line);
	cred = os_zalloc(sizeof(*cred));
	if (cred == NULL)
		return NULL;
	cred->id = id;
	cred->sim_num = DEFAULT_USER_SELECTED_SIM;

	while (wpa_config_get_line(buf, sizeof(buf), f, line, &pos)) {
		if (os_strcmp(pos, "}") == 0) {
			end = 1;
			break;
		}

		pos2 = os_strchr(pos, '=');
		if (pos2 == NULL) {
			wpa_printf(MSG_ERROR, "Line %d: Invalid cred line "
				   "'%s'.", *line, pos);
			errors++;
			continue;
		}

		*pos2++ = '\0';
		if (*pos2 == '"') {
			if (os_strchr(pos2 + 1, '"') == NULL) {
				wpa_printf(MSG_ERROR, "Line %d: invalid "
					   "quotation '%s'.", *line, pos2);
				errors++;
				continue;
			}
		}

		if (wpa_config_set_cred(cred, pos, pos2, *line) < 0)
			errors++;
	}

	if (!end) {
		wpa_printf(MSG_ERROR, "Line %d: cred block was not "
			   "terminated properly.", *line);
		errors++;
	}

	if (errors) {
		wpa_config_free_cred(cred);
		cred = NULL;
	}

	return cred;
}