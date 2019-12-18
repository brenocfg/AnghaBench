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
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  test_client (int,char const**) ; 
 int /*<<< orphan*/  test_get_principal_name (int,char const**) ; 
 int /*<<< orphan*/  test_server (int,char const**) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, const char **argv)
{

	if (argc < 2)
		usage();
	if (!strcmp(argv[1], "client"))
		test_client(argc - 1, argv + 1);
	else if (!strcmp(argv[1], "server"))
		test_server(argc - 1, argv + 1);
	else if (!strcmp(argv[1], "principal"))
		test_get_principal_name(argc - 1, argv + 1);
	else
		usage();

	return (0);
}