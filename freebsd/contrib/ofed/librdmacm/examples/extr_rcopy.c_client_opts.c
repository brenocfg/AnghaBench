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
 char* dst_addr ; 
 char* dst_file ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  show_usage (char*) ; 
 char* src_file ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void client_opts(int argc, char **argv)
{
	int op;

	if (argc < 3)
		show_usage(argv[0]);

	src_file = argv[1];
	dst_addr = argv[2];
	dst_file = strchr(dst_addr, ':');
	if (dst_file) {
		*dst_file = '\0';
		dst_file++;
	}
	if (!dst_file)
		dst_file = src_file;

	while ((op = getopt(argc, argv, "p:")) != -1) {
		switch (op) {
		case 'p':
			port = optarg;
			break;
		default:
			show_usage(argv[0]);
		}
	}

}