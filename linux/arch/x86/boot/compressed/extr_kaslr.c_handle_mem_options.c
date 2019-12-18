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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_cmd_line_ptr () ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  mem_avoid_memmap (char*) ; 
 int /*<<< orphan*/  mem_limit ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memparse (char*,char**) ; 
 char* next_arg (char*,char**,char**) ; 
 int /*<<< orphan*/  parse_gb_huge_pages (char*,char*) ; 
 char* skip_spaces (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void handle_mem_options(void)
{
	char *args = (char *)get_cmd_line_ptr();
	size_t len = strlen((char *)args);
	char *tmp_cmdline;
	char *param, *val;
	u64 mem_size;

	if (!strstr(args, "memmap=") && !strstr(args, "mem=") &&
		!strstr(args, "hugepages"))
		return;

	tmp_cmdline = malloc(len + 1);
	if (!tmp_cmdline)
		error("Failed to allocate space for tmp_cmdline");

	memcpy(tmp_cmdline, args, len);
	tmp_cmdline[len] = 0;
	args = tmp_cmdline;

	/* Chew leading spaces */
	args = skip_spaces(args);

	while (*args) {
		args = next_arg(args, &param, &val);
		/* Stop at -- */
		if (!val && strcmp(param, "--") == 0) {
			warn("Only '--' specified in cmdline");
			goto out;
		}

		if (!strcmp(param, "memmap")) {
			mem_avoid_memmap(val);
		} else if (strstr(param, "hugepages")) {
			parse_gb_huge_pages(param, val);
		} else if (!strcmp(param, "mem")) {
			char *p = val;

			if (!strcmp(p, "nopentium"))
				continue;
			mem_size = memparse(p, &p);
			if (mem_size == 0)
				goto out;

			mem_limit = mem_size;
		}
	}

out:
	free(tmp_cmdline);
	return;
}