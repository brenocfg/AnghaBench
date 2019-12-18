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
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_policy (char*,char*,char*) ; 
 char* configfile ; 
 int /*<<< orphan*/  delete_policy (char*) ; 
 int /*<<< orphan*/  dump_policy () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_policy () ; 
 int /*<<< orphan*/  get_policy () ; 
 int /*<<< orphan*/  make_policy_fromfile (char*) ; 
 int /*<<< orphan*/  policyhead ; 
 int /*<<< orphan*/  set_policy () ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	TAILQ_INIT(&policyhead);

	if (argc == 1 || strcasecmp(argv[1], "show") == 0) {
		get_policy();
		dump_policy();
	} else if (strcasecmp(argv[1], "add") == 0) {
		if (argc < 5)
			usage();
		add_policy(argv[2], argv[3], argv[4]);
	} else if (strcasecmp(argv[1], "delete") == 0) {
		if (argc < 3)
			usage();
		delete_policy(argv[2]);
	} else if (strcasecmp(argv[1], "flush") == 0) {
		get_policy();
		flush_policy();
	} else if (strcasecmp(argv[1], "install") == 0) {
		if (argc < 3)
			usage();
		configfile = argv[2];
		make_policy_fromfile(configfile);
		set_policy();
	} else
		usage();

	exit(0);
}