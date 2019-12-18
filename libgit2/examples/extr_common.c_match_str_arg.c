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
struct args_info {char** argv; size_t pos; int argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 size_t is_prefixed (char const*,char const*) ; 

int match_str_arg(
	const char **out, struct args_info *args, const char *opt)
{
	const char *found = args->argv[args->pos];
	size_t len = is_prefixed(found, opt);

	if (!len)
		return 0;

	if (!found[len]) {
		if (args->pos + 1 == args->argc)
			fatal("expected value following argument", opt);
		args->pos += 1;
		*out = args->argv[args->pos];
		return 1;
	}

	if (found[len] == '=') {
		*out = found + len + 1;
		return 1;
	}

	return 0;
}