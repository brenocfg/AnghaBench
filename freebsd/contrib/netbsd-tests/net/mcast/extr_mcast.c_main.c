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
 char* HOST_V4 ; 
 char* HOST_V4MAPPED ; 
 char* HOST_V6 ; 
 char* PORT_V4 ; 
 char* PORT_V4MAPPED ; 
 char* PORT_V6 ; 
 size_t TOTAL ; 
 size_t atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  run (char const*,char const*,size_t,int,int) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
	const char *host, *port;
	int c;
	size_t n;
	bool conn, bug;

	host = HOST_V4;
	port = PORT_V4;
	n = TOTAL;
	bug = conn = false;

	while ((c = getopt(argc, argv, "46bcdmn:")) != -1)
		switch (c) {
		case '4':
			host = HOST_V4;
			port = PORT_V4;
			break;
		case '6':
			host = HOST_V6;
			port = PORT_V6;
			break;
		case 'b':
			bug = true;
			break;
		case 'c':
			conn = true;
			break;
		case 'd':
			debug++;
			break;
		case 'm':
			host = HOST_V4MAPPED;
			port = PORT_V4MAPPED;
			break;
		case 'n':
			n = atoi(optarg);
			break;
		default:
			fprintf(stderr, "Usage: %s [-cdm46] [-n <tot>]",
			    getprogname());
			return 1;
		}

	run(host, port, n, conn, bug);
	return 0;
}