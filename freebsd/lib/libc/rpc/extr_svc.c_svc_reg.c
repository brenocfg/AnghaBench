#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct svc_callout {void (* sc_dispatch ) (struct svc_req*,TYPE_1__*) ;char* sc_netid; struct svc_callout* sc_next; int /*<<< orphan*/  sc_vers; int /*<<< orphan*/  sc_prog; } ;
struct netconfig {char* nc_netid; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_5__ {char* xp_netid; int /*<<< orphan*/  xp_ltaddr; int /*<<< orphan*/  xp_fd; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct netconfig* __rpcgettp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freenetconfigent (struct netconfig*) ; 
 struct svc_callout* mem_alloc (int) ; 
 int /*<<< orphan*/  rpcb_set (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct netconfig*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wrlock (int /*<<< orphan*/ *) ; 
 void* strdup (char*) ; 
 struct svc_callout* svc_find (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct svc_callout**,char*) ; 
 struct svc_callout* svc_head ; 
 int /*<<< orphan*/  svc_lock ; 

bool_t
svc_reg(SVCXPRT *xprt, const rpcprog_t prog, const rpcvers_t vers,
    void (*dispatch)(struct svc_req *, SVCXPRT *),
    const struct netconfig *nconf)
{
	bool_t dummy;
	struct svc_callout *prev;
	struct svc_callout *s;
	struct netconfig *tnconf;
	char *netid = NULL;
	int flag = 0;

/* VARIABLES PROTECTED BY svc_lock: s, prev, svc_head */

	if (xprt->xp_netid) {
		netid = strdup(xprt->xp_netid);
		flag = 1;
	} else if (nconf && nconf->nc_netid) {
		netid = strdup(nconf->nc_netid);
		flag = 1;
	} else if ((tnconf = __rpcgettp(xprt->xp_fd)) != NULL) {
		netid = strdup(tnconf->nc_netid);
		flag = 1;
		freenetconfigent(tnconf);
	} /* must have been created with svc_raw_create */
	if ((netid == NULL) && (flag == 1)) {
		return (FALSE);
	}

	rwlock_wrlock(&svc_lock);
	if ((s = svc_find(prog, vers, &prev, netid)) != NULL) {
		free(netid);
		if (s->sc_dispatch == dispatch)
			goto rpcb_it; /* he is registering another xptr */
		rwlock_unlock(&svc_lock);
		return (FALSE);
	}
	s = mem_alloc(sizeof (struct svc_callout));
	if (s == NULL) {
		free(netid);
		rwlock_unlock(&svc_lock);
		return (FALSE);
	}

	s->sc_prog = prog;
	s->sc_vers = vers;
	s->sc_dispatch = dispatch;
	s->sc_netid = netid;
	s->sc_next = svc_head;
	svc_head = s;

	if ((xprt->xp_netid == NULL) && (flag == 1) && netid)
		((SVCXPRT *) xprt)->xp_netid = strdup(netid);

rpcb_it:
	rwlock_unlock(&svc_lock);
	/* now register the information with the local binder service */
	if (nconf) {
		/*LINTED const castaway*/
		dummy = rpcb_set(prog, vers, (struct netconfig *) nconf,
		&((SVCXPRT *) xprt)->xp_ltaddr);
		return (dummy);
	}
	return (TRUE);
}