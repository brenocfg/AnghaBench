#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * buf; } ;
struct svc_dg_data {TYPE_3__ su_srcaddr; } ;
struct fdlist {TYPE_2__* nconf; struct fdlist* next; } ;
struct TYPE_9__ {int /*<<< orphan*/  nc_netid; } ;
struct TYPE_8__ {scalar_t__ xp_p2; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 char* addrmerge (TYPE_3__*,char*,char*,char*) ; 
 scalar_t__ check_bound (struct fdlist*,char*) ; 
 scalar_t__ debugging ; 
 struct fdlist* fdhead ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* nullstring ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* svc_getrpccaller (TYPE_1__*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* taddr2uaddr (TYPE_2__*,TYPE_3__*) ; 

char *
mergeaddr(SVCXPRT *xprt, char *netid, char *uaddr, char *saddr)
{
	struct fdlist *fdl;
	struct svc_dg_data *dg_data;
	char *c_uaddr, *s_uaddr, *m_uaddr, *allocated_uaddr = NULL;

	for (fdl = fdhead; fdl; fdl = fdl->next)
		if (strcmp(fdl->nconf->nc_netid, netid) == 0)
			break;
	if (fdl == NULL)
		return (NULL);
	if (check_bound(fdl, uaddr) == FALSE)
		/* that server died */
		return (nullstring);
	/*
	 * Try to determine the local address on which the client contacted us,
	 * so we can send a reply from the same address.  If it's unknown, then
	 * try to determine which address the client used, and pick a nearby
	 * local address.
	 *
	 * If saddr is not NULL, the remote client may have included the
	 * address by which it contacted us.  Use that for the "client" uaddr,
	 * otherwise use the info from the SVCXPRT.
	 */
	dg_data = (struct svc_dg_data*)xprt->xp_p2;
	if (dg_data != NULL && dg_data->su_srcaddr.buf != NULL) {
		c_uaddr = taddr2uaddr(fdl->nconf, &dg_data->su_srcaddr);
		allocated_uaddr = c_uaddr;
	}
	else if (saddr != NULL) {
		c_uaddr = saddr;
	} else {
		c_uaddr = taddr2uaddr(fdl->nconf, svc_getrpccaller(xprt));
		allocated_uaddr = c_uaddr;
	}
	if (c_uaddr == NULL) {
		syslog(LOG_ERR, "taddr2uaddr failed for %s",
			fdl->nconf->nc_netid);
		return (NULL);
	}

#ifdef ND_DEBUG
	if (debugging) {
		if (saddr == NULL) {
			fprintf(stderr, "mergeaddr: client uaddr = %s\n",
			    c_uaddr);
		} else {
			fprintf(stderr, "mergeaddr: contact uaddr = %s\n",
			    c_uaddr);
		}
	}
#endif
	s_uaddr = uaddr;
	/*
	 * This is all we should need for IP 4 and 6
	 */
	m_uaddr = addrmerge(svc_getrpccaller(xprt), s_uaddr, c_uaddr, netid);
#ifdef ND_DEBUG
	if (debugging)
		fprintf(stderr, "mergeaddr: uaddr = %s, merged uaddr = %s\n",
				uaddr, m_uaddr);
#endif
	free(allocated_uaddr);
	return (m_uaddr);
}