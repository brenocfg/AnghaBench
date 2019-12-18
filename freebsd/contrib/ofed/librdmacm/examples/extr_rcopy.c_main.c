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
 int /*<<< orphan*/  client_opts (int,char**) ; 
 int client_run () ; 
 int /*<<< orphan*/  server_opts (int,char**) ; 
 int server_run () ; 

int main(int argc, char **argv)
{
	int ret;

	if (argc == 1 || argv[1][0] == '-') {
		server_opts(argc, argv);
		ret = server_run();
	} else {
		client_opts(argc, argv);
		ret = client_run();
	}

	return ret;
}