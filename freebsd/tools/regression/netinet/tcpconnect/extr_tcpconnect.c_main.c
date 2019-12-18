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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tcpconnect_client (int,char**) ; 
 int /*<<< orphan*/  tcpconnect_server (int,char**) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{

	if (argc < 2)
		usage();

	if (strcmp(argv[1], "server") == 0)
		tcpconnect_server(argc - 2, argv + 2);
	else if (strcmp(argv[1], "client") == 0)
		tcpconnect_client(argc - 2, argv + 2);
	else
		usage();

	exit(0);
}