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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_RANDOMIZE_BASE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  command_line_buf ; 
 int /*<<< orphan*/  early_command_line ; 
 scalar_t__ kaslr_enabled ; 
 int kstrtobool (char*,int*) ; 
 int /*<<< orphan*/  memory_end ; 
 int memory_end_set ; 
 int /*<<< orphan*/  memparse (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modify_fac_list (char*) ; 
 char* next_arg (char*,char**,char**) ; 
 int noexec_disabled ; 
 int /*<<< orphan*/  round_down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc_size ; 

void parse_boot_command_line(void)
{
	char *param, *val;
	bool enabled;
	char *args;
	int rc;

	kaslr_enabled = IS_ENABLED(CONFIG_RANDOMIZE_BASE);
	args = strcpy(command_line_buf, early_command_line);
	while (*args) {
		args = next_arg(args, &param, &val);

		if (!strcmp(param, "mem") && val) {
			memory_end = round_down(memparse(val, NULL), PAGE_SIZE);
			memory_end_set = 1;
		}

		if (!strcmp(param, "vmalloc") && val)
			vmalloc_size = round_up(memparse(val, NULL), PAGE_SIZE);

		if (!strcmp(param, "noexec")) {
			rc = kstrtobool(val, &enabled);
			if (!rc && !enabled)
				noexec_disabled = 1;
		}

		if (!strcmp(param, "facilities") && val)
			modify_fac_list(val);

		if (!strcmp(param, "nokaslr"))
			kaslr_enabled = 0;
	}
}