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
struct wpa_config_blob {int dummy; } ;
struct wpa_config {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 char* os_strchr (char*,char) ; 
 struct wpa_config_blob* wpa_config_read_blob (int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/  wpa_config_set_blob (struct wpa_config*,struct wpa_config_blob*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int wpa_config_process_blob(struct wpa_config *config, FILE *f,
				   int *line, char *bname)
{
	char *name_end;
	struct wpa_config_blob *blob;

	name_end = os_strchr(bname, '=');
	if (name_end == NULL) {
		wpa_printf(MSG_ERROR, "Line %d: no blob name terminator",
			   *line);
		return -1;
	}
	*name_end = '\0';

	blob = wpa_config_read_blob(f, line, bname);
	if (blob == NULL) {
		wpa_printf(MSG_ERROR, "Line %d: failed to read blob %s",
			   *line, bname);
		return -1;
	}
	wpa_config_set_blob(config, blob);
	return 0;
}