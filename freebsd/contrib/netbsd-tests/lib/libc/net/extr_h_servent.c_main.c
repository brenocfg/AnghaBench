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
struct servent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  endservent () ; 
 int getopt (int,char**,char*) ; 
 struct servent* getservbyname (char const*,char const*) ; 
 struct servent* getservbyport (int /*<<< orphan*/ ,char const*) ; 
 struct servent* getservent () ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int /*<<< orphan*/  pserv (struct servent*) ; 
 int /*<<< orphan*/  setservent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct servent *svp;
	const char *port = NULL, *proto = NULL, *name = NULL;
	int c;

	while ((c = getopt(argc, argv, "p:n:P:")) != -1) {
		switch (c) {
		case 'n':
			name = optarg;
			break;
		case 'p':
			port = optarg;
			break;
		case 'P':
			proto = optarg;
			break;
		default:
			usage();
		}
	}

	if (port && name)
		usage();
	if (port) {
		if ((svp = getservbyport(htons(atoi(port)), proto)) != NULL)
			pserv(svp);
		return 0;
	}
	if (name) {
		if ((svp = getservbyname(name, proto)) != NULL)
			pserv(svp);
		return 0;
	}

	setservent(0);
	while ((svp = getservent()) != NULL)
		pserv(svp);
	endservent();
	return 0;
}