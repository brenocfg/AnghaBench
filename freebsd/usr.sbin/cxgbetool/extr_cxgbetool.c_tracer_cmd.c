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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int EINVAL ; 
 int set_tracer (scalar_t__,int,char const**) ; 
 int show_tracers () ; 
 char* str_to_number (char const*,int /*<<< orphan*/ *,long long*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int tracer_onoff (scalar_t__,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
tracer_cmd(int argc, const char *argv[])
{
	long long val;
	uint8_t idx;
	char *s;

	if (argc == 0) {
		warnx("tracer: no arguments.");
		return (EINVAL);
	};

	/* list */
	if (strcmp(argv[0], "list") == 0) {
		if (argc != 1)
			warnx("trailing arguments after \"list\" ignored.");

		return show_tracers();
	}

	/* <idx> ... */
	s = str_to_number(argv[0], NULL, &val);
	if (*s || val > 0xff) {
		warnx("\"%s\" is neither an index nor a tracer subcommand.",
		    argv[0]);
		return (EINVAL);
	}
	idx = (int8_t)val;

	/* <idx> disable */
	if (argc == 2 && strcmp(argv[1], "disable") == 0)
		return tracer_onoff(idx, 0);

	/* <idx> enable */
	if (argc == 2 && strcmp(argv[1], "enable") == 0)
		return tracer_onoff(idx, 1);

	/* <idx> ... */
	return set_tracer(idx, argc - 1, argv + 1);
}