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
 int /*<<< orphan*/  do_show (int,int /*<<< orphan*/ *) ; 
 int feature_present (char*) ; 
 int /*<<< orphan*/  flow_cache_print ; 
 int /*<<< orphan*/  flow_cache_print6 ; 
 int /*<<< orphan*/  flow_cache_print6_verbose ; 
 int /*<<< orphan*/  flow_cache_print_verbose ; 
 int human ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void
ctl_show(int argc, char **argv)
{
	int ipv4, ipv6, verbose = 0;

	ipv4 = feature_present("inet");
	ipv6 = feature_present("inet6");

	if (argc > 0 && !strncmp(argv[0], "ipv4", 4)) {
		ipv6 = 0;
		argc--;
		argv++;
	}
	if (argc > 0 && !strncmp(argv[0], "ipv6", 4)) {
		ipv4 = 0;
		argc--;
		argv++;
	}

	if (argc > 0 && !strncmp(argv[0], "verbose", strlen(argv[0])))
		verbose = 1;

	if (argc > 0 && !strncmp(argv[0], "human", strlen(argv[0])))
		human = 1;

#ifdef INET
	if (ipv4) {
		if (verbose)
			do_show(4, &flow_cache_print_verbose);
		else
			do_show(4, &flow_cache_print);
	}
#endif

#ifdef INET6
	if (ipv6) {
		if (verbose)
			do_show(6, &flow_cache_print6_verbose);
		else
			do_show(6, &flow_cache_print6);
	}
#endif
}