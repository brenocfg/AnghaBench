#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; } ;
struct config_set {int dummy; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  early_config_cb ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (char const*,int*) ; 
 int /*<<< orphan*/  git_config_get_int (char const*,int*) ; 
 int /*<<< orphan*/  git_config_get_string_const (char const*,char const**) ; 
 int /*<<< orphan*/  git_config_get_value (char const*,char const**) ; 
 struct string_list* git_config_get_value_multi (char const*) ; 
 int git_configset_add_file (struct config_set*,char const*) ; 
 int /*<<< orphan*/  git_configset_clear (struct config_set*) ; 
 int /*<<< orphan*/  git_configset_get_value (struct config_set*,char const*,char const**) ; 
 struct string_list* git_configset_get_value_multi (struct config_set*,char const*) ; 
 int /*<<< orphan*/  git_configset_init (struct config_set*) ; 
 int /*<<< orphan*/  iterate_cb ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_early_config (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int cmd__config(int argc, const char **argv)
{
	int i, val;
	const char *v;
	const struct string_list *strptr;
	struct config_set cs;

	if (argc == 3 && !strcmp(argv[1], "read_early_config")) {
		read_early_config(early_config_cb, (void *)argv[2]);
		return 0;
	}

	setup_git_directory();

	git_configset_init(&cs);

	if (argc < 2) {
		fprintf(stderr, "Please, provide a command name on the command-line\n");
		goto exit1;
	} else if (argc == 3 && !strcmp(argv[1], "get_value")) {
		if (!git_config_get_value(argv[2], &v)) {
			if (!v)
				printf("(NULL)\n");
			else
				printf("%s\n", v);
			goto exit0;
		} else {
			printf("Value not found for \"%s\"\n", argv[2]);
			goto exit1;
		}
	} else if (argc == 3 && !strcmp(argv[1], "get_value_multi")) {
		strptr = git_config_get_value_multi(argv[2]);
		if (strptr) {
			for (i = 0; i < strptr->nr; i++) {
				v = strptr->items[i].string;
				if (!v)
					printf("(NULL)\n");
				else
					printf("%s\n", v);
			}
			goto exit0;
		} else {
			printf("Value not found for \"%s\"\n", argv[2]);
			goto exit1;
		}
	} else if (argc == 3 && !strcmp(argv[1], "get_int")) {
		if (!git_config_get_int(argv[2], &val)) {
			printf("%d\n", val);
			goto exit0;
		} else {
			printf("Value not found for \"%s\"\n", argv[2]);
			goto exit1;
		}
	} else if (argc == 3 && !strcmp(argv[1], "get_bool")) {
		if (!git_config_get_bool(argv[2], &val)) {
			printf("%d\n", val);
			goto exit0;
		} else {
			printf("Value not found for \"%s\"\n", argv[2]);
			goto exit1;
		}
	} else if (argc == 3 && !strcmp(argv[1], "get_string")) {
		if (!git_config_get_string_const(argv[2], &v)) {
			printf("%s\n", v);
			goto exit0;
		} else {
			printf("Value not found for \"%s\"\n", argv[2]);
			goto exit1;
		}
	} else if (!strcmp(argv[1], "configset_get_value")) {
		for (i = 3; i < argc; i++) {
			int err;
			if ((err = git_configset_add_file(&cs, argv[i]))) {
				fprintf(stderr, "Error (%d) reading configuration file %s.\n", err, argv[i]);
				goto exit2;
			}
		}
		if (!git_configset_get_value(&cs, argv[2], &v)) {
			if (!v)
				printf("(NULL)\n");
			else
				printf("%s\n", v);
			goto exit0;
		} else {
			printf("Value not found for \"%s\"\n", argv[2]);
			goto exit1;
		}
	} else if (!strcmp(argv[1], "configset_get_value_multi")) {
		for (i = 3; i < argc; i++) {
			int err;
			if ((err = git_configset_add_file(&cs, argv[i]))) {
				fprintf(stderr, "Error (%d) reading configuration file %s.\n", err, argv[i]);
				goto exit2;
			}
		}
		strptr = git_configset_get_value_multi(&cs, argv[2]);
		if (strptr) {
			for (i = 0; i < strptr->nr; i++) {
				v = strptr->items[i].string;
				if (!v)
					printf("(NULL)\n");
				else
					printf("%s\n", v);
			}
			goto exit0;
		} else {
			printf("Value not found for \"%s\"\n", argv[2]);
			goto exit1;
		}
	} else if (!strcmp(argv[1], "iterate")) {
		git_config(iterate_cb, NULL);
		goto exit0;
	}

	die("%s: Please check the syntax and the function name", argv[0]);

exit0:
	git_configset_clear(&cs);
	return 0;

exit1:
	git_configset_clear(&cs);
	return 1;

exit2:
	git_configset_clear(&cs);
	return 2;
}