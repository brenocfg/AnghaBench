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
struct protoent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  endprotoent () ; 
 int getopt (int,char**,char*) ; 
 struct protoent* getprotobyname (char const*) ; 
 struct protoent* getprotobynumber (int /*<<< orphan*/ ) ; 
 struct protoent* getprotoent () ; 
 char* optarg ; 
 int /*<<< orphan*/  pserv (struct protoent*) ; 
 int /*<<< orphan*/  setprotoent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct protoent *prp;
	const char *proto = NULL, *name = NULL;
	int c;

	while ((c = getopt(argc, argv, "p:n:")) != -1) {
		switch (c) {
		case 'n':
			name = optarg;
			break;
		case 'p':
			proto = optarg;
			break;
		default:
			usage();
		}
	}

	if (proto && name)
		usage();
	if (proto) {
		if ((prp = getprotobynumber(atoi(proto))) != NULL)
			pserv(prp);
		return 0;
	}
	if (name) {
		if ((prp = getprotobyname(name)) != NULL)
			pserv(prp);
		return 0;
	}

	setprotoent(0);
	while ((prp = getprotoent()) != NULL)
		pserv(prp);
	endprotoent();
	return 0;
}