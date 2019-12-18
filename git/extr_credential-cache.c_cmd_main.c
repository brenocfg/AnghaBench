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
struct option {int dummy; } ;

/* Variables and functions */
 int FLAG_RELAY ; 
 int FLAG_SPAWN ; 
 struct option OPT_END () ; 
 struct option OPT_INTEGER (int /*<<< orphan*/ ,char*,int*,char*) ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char**,char*,char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  do_cache (char*,char const*,int,int) ; 
 char* get_socket_path () ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option*) ; 

int cmd_main(int argc, const char **argv)
{
	char *socket_path = NULL;
	int timeout = 900;
	const char *op;
	const char * const usage[] = {
		"git credential-cache [<options>] <action>",
		NULL
	};
	struct option options[] = {
		OPT_INTEGER(0, "timeout", &timeout,
			    "number of seconds to cache credentials"),
		OPT_STRING(0, "socket", &socket_path, "path",
			   "path of cache-daemon socket"),
		OPT_END()
	};

	argc = parse_options(argc, argv, NULL, options, usage, 0);
	if (!argc)
		usage_with_options(usage, options);
	op = argv[0];

	if (!socket_path)
		socket_path = get_socket_path();
	if (!socket_path)
		die("unable to find a suitable socket path; use --socket");

	if (!strcmp(op, "exit"))
		do_cache(socket_path, op, timeout, 0);
	else if (!strcmp(op, "get") || !strcmp(op, "erase"))
		do_cache(socket_path, op, timeout, FLAG_RELAY);
	else if (!strcmp(op, "store"))
		do_cache(socket_path, op, timeout, FLAG_RELAY|FLAG_SPAWN);
	else
		; /* ignore unknown operation */

	return 0;
}