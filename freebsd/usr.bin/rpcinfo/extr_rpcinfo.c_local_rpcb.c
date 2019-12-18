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
typedef  int /*<<< orphan*/  u_long ;
struct netconfig {int /*<<< orphan*/ * nc_protofmly; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  NC_LOOPBACK ; 
 int /*<<< orphan*/ * clnt_tp_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netconfig*) ; 
 int /*<<< orphan*/  endnetconfig (void*) ; 
 struct netconfig* getnetconfig (void*) ; 
 int /*<<< orphan*/  nc_sperror () ; 
 void* setnetconfig () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CLIENT *
local_rpcb(u_long prog, u_long vers)
{
	void *localhandle;
	struct netconfig *nconf;
	CLIENT *clnt;

	localhandle = setnetconfig();
	while ((nconf = getnetconfig(localhandle)) != NULL) {
		if (nconf->nc_protofmly != NULL &&
		    strcmp(nconf->nc_protofmly, NC_LOOPBACK) == 0)
			break;
	}
	if (nconf == NULL) {
		warnx("getnetconfig: %s", nc_sperror());
		return (NULL);
	}

	clnt = clnt_tp_create(NULL, prog, vers, nconf);
	endnetconfig(localhandle);
	return clnt;
}