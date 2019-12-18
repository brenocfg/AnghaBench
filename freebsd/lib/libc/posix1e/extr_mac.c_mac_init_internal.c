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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int LINE_MAX ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 char* MAC_CONFFILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* getenv (char*) ; 
 int internal_initialized ; 
 int /*<<< orphan*/  issetugid () ; 
 int /*<<< orphan*/  label_default_head ; 
 int mac_add_type (char*,char*) ; 
 int /*<<< orphan*/  mac_destroy_internal () ; 
 char* next_token (char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
mac_init_internal(int ignore_errors)
{
	const char *filename;
	char line[LINE_MAX];
	FILE *file;
	int error;

	error = 0;

	LIST_INIT(&label_default_head);

	if (!issetugid() && getenv("MAC_CONFFILE") != NULL)
		filename = getenv("MAC_CONFFILE");
	else
		filename = MAC_CONFFILE;
	file = fopen(filename, "re");
	if (file == NULL)
		return (0);

	while (fgets(line, LINE_MAX, file)) {
		char *comment, *parse, *statement;

		if (line[strlen(line)-1] == '\n')
			line[strlen(line)-1] = '\0';
		else {
			if (ignore_errors)
				continue;
			fclose(file);
			error = EINVAL;
			goto just_return;
		}

		/* Remove any comment. */
		comment = line;
		parse = strsep(&comment, "#");

		/* Blank lines OK. */
		statement = next_token(&parse);
		if (statement == NULL)
			continue;

		if (strcmp(statement, "default_labels") == 0) {
			char *name, *labels;

			name = next_token(&parse);
			labels = next_token(&parse);
			if (name == NULL || labels == NULL ||
			    next_token(&parse) != NULL) {
				if (ignore_errors)
					continue;
				error = EINVAL;
				fclose(file);
				goto just_return;
			}

			if (mac_add_type(name, labels) == -1) {
				if (ignore_errors)
					continue;
				fclose(file);
				goto just_return;
			}
		} else if (strcmp(statement, "default_ifnet_labels") == 0 ||
		    strcmp(statement, "default_file_labels") == 0 ||
		    strcmp(statement, "default_process_labels") == 0) {
			char *labels, *type;

			if (strcmp(statement, "default_ifnet_labels") == 0)
				type = "ifnet";
			else if (strcmp(statement, "default_file_labels") == 0)
				type = "file";
			else if (strcmp(statement, "default_process_labels") ==
			    0)
				type = "process";

			labels = next_token(&parse);
			if (labels == NULL || next_token(&parse) != NULL) {
				if (ignore_errors)
					continue;
				error = EINVAL;
				fclose(file);
				goto just_return;
			}

			if (mac_add_type(type, labels) == -1) {
				if (ignore_errors)
					continue;
				fclose(file);
				goto just_return;
			}
		} else {
			if (ignore_errors)
				continue;
			fclose(file);
			error = EINVAL;
			goto just_return;
		}
	}

	fclose(file);

	internal_initialized = 1;

just_return:
	if (error != 0)
		mac_destroy_internal();
	return (error);
}