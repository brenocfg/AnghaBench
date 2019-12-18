#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netid_af {int dummy; } ;
struct netconfig {int dummy; } ;
struct __rpc_sockinfo {scalar_t__ si_af; scalar_t__ si_proto; } ;
struct TYPE_2__ {scalar_t__ af; scalar_t__ protocol; char* netid; } ;

/* Variables and functions */
 int /*<<< orphan*/  freenetconfigent (struct netconfig*) ; 
 struct netconfig* getnetconfigent (char*) ; 
 TYPE_1__* na_cvt ; 
 scalar_t__ strcmp (char*,char*) ; 

int
__rpc_sockinfo2netid(struct __rpc_sockinfo *sip, const char **netid)
{
	int i;
	struct netconfig *nconf;

	nconf = getnetconfigent("local");

	for (i = 0; i < (sizeof na_cvt) / (sizeof (struct netid_af)); i++) {
		if (na_cvt[i].af == sip->si_af &&
		    na_cvt[i].protocol == sip->si_proto) {
			if (strcmp(na_cvt[i].netid, "local") == 0 && nconf == NULL) {
				if (netid)
					*netid = "unix";
			} else {
				if (netid)
					*netid = na_cvt[i].netid;
			}
			if (nconf != NULL)
				freenetconfigent(nconf);
			return 1;
		}
	}
	if (nconf != NULL)
		freenetconfigent(nconf);

	return 0;
}