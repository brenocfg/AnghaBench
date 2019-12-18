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
struct netconfig {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*,...) ; 
 struct netconfig* getnetconfigent (char*) ; 
 int /*<<< orphan*/  getprognum (char*) ; 
 int /*<<< orphan*/  getvers (char*) ; 
 scalar_t__ rpcb_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netconfig*) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
deletereg(char *netid, int argc, char **argv)
{
	struct netconfig *nconf = NULL;

	if (argc != 2)
		usage();
	if (netid) {
		nconf = getnetconfigent(netid);
		if (nconf == NULL)
			errx(1, "netid %s not supported", netid);
	}
	if ((rpcb_unset(getprognum(argv[0]), getvers(argv[1]), nconf)) == 0)
		errx(1,
	"could not delete registration for prog %s version %s",
			argv[0], argv[1]);
}