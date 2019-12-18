#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct ypall_callback {int /*<<< orphan*/ * data; int /*<<< orphan*/  foreach; } ;
struct TYPE_3__ {char* alias; char* name; } ;

/* Variables and functions */
#define  YPERR_YPBIND 128 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int key ; 
 size_t nitems (TYPE_1__*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  printit ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int yp_all (char*,char*,struct ypall_callback*) ; 
 int /*<<< orphan*/  yp_get_default_domain (char**) ; 
 TYPE_1__* ypaliases ; 
 int /*<<< orphan*/  yperr_string (int) ; 

int
main(int argc, char *argv[])
{
	char *domain = NULL, *inmap;
	struct ypall_callback ypcb;
	int c, notrans, r;
	u_int i;

	notrans = key = 0;
	while ((c = getopt(argc, argv, "xd:kt")) != -1)
		switch (c) {
		case 'x':
			for (i = 0; i < nitems(ypaliases); i++)
				printf("Use \"%s\" for \"%s\"\n",
				    ypaliases[i].alias, ypaliases[i].name);
			exit(0);
		case 'd':
			domain = optarg;
			break;
		case 't':
			notrans = 1;
			break;
		case 'k':
			key = 1;
			break;
		default:
			usage();
		}

	if (optind + 1 != argc)
		usage();

	if (domain == NULL)
		yp_get_default_domain(&domain);

	inmap = argv[optind];
	if (notrans == 0) {
		for (i = 0; i < nitems(ypaliases); i++)
			if (strcmp(inmap, ypaliases[i].alias) == 0)
				inmap = ypaliases[i].name;
	}
	ypcb.foreach = printit;
	ypcb.data = NULL;

	r = yp_all(domain, inmap, &ypcb);
	switch (r) {
	case 0:
		break;
	case YPERR_YPBIND:
		errx(1, "not running ypbind");
	default:
		errx(1, "no such map %s. Reason: %s",
		    inmap, yperr_string(r));
	}
	exit(0);
}