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
struct TYPE_2__ {struct addrinfo* gt_addrinfo; } ;
struct grouplist {scalar_t__ gr_type; TYPE_1__ gr_ptr; struct grouplist* gr_next; } ;
struct addrinfo {char* ai_canonname; struct addrinfo* ai_next; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_protocol; } ;
typedef  int /*<<< orphan*/  host ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 scalar_t__ GT_HOST ; 
 scalar_t__ GT_IGNORE ; 
 scalar_t__ GT_NULL ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sacmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
get_host(char *cp, struct grouplist *grp, struct grouplist *tgrp)
{
	struct grouplist *checkgrp;
	struct addrinfo *ai, *tai, hints;
	int ecode;
	char host[NI_MAXHOST];

	if (grp->gr_type != GT_NULL) {
		syslog(LOG_ERR, "Bad netgroup type for ip host %s", cp);
		return (1);
	}
	memset(&hints, 0, sizeof hints);
	hints.ai_flags = AI_CANONNAME;
	hints.ai_protocol = IPPROTO_UDP;
	ecode = getaddrinfo(cp, NULL, &hints, &ai);
	if (ecode != 0) {
		syslog(LOG_ERR,"can't get address info for host %s", cp);
		return 1;
	}
	grp->gr_ptr.gt_addrinfo = ai;
	while (ai != NULL) {
		if (ai->ai_canonname == NULL) {
			if (getnameinfo(ai->ai_addr, ai->ai_addrlen, host,
			    sizeof host, NULL, 0, NI_NUMERICHOST) != 0)
				strlcpy(host, "?", sizeof(host));
			ai->ai_canonname = strdup(host);
			ai->ai_flags |= AI_CANONNAME;
		}
		if (debug)
			fprintf(stderr, "got host %s\n", ai->ai_canonname);
		/*
		 * Sanity check: make sure we don't already have an entry
		 * for this host in the grouplist.
		 */
		for (checkgrp = tgrp; checkgrp != NULL;
		    checkgrp = checkgrp->gr_next) {
			if (checkgrp->gr_type != GT_HOST)
				continue;
			for (tai = checkgrp->gr_ptr.gt_addrinfo; tai != NULL;
			    tai = tai->ai_next) {
				if (sacmp(tai->ai_addr, ai->ai_addr, NULL) != 0)
					continue;
				if (debug)
					fprintf(stderr,
					    "ignoring duplicate host %s\n",
					    ai->ai_canonname);
				grp->gr_type = GT_IGNORE;
				return (0);
			}
		}
		ai = ai->ai_next;
	}
	grp->gr_type = GT_HOST;
	return (0);
}