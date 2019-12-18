#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct svc_dg_data {scalar_t__ su_xid; scalar_t__ su_cache; } ;
struct TYPE_10__ {scalar_t__ cb_proc; scalar_t__ cb_vers; scalar_t__ cb_prog; } ;
struct rpc_msg {TYPE_2__ rm_call; } ;
struct netconfig {int dummy; } ;
struct cl_cache {int uc_proc; int uc_vers; int uc_prog; TYPE_3__** uc_entries; } ;
typedef  TYPE_3__* cache_ptr ;
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct TYPE_12__ {TYPE_5__ xp_rtaddr; int /*<<< orphan*/  xp_netid; } ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct TYPE_11__ {scalar_t__ cache_xid; scalar_t__ cache_proc; scalar_t__ cache_vers; scalar_t__ cache_prog; char* cache_reply; size_t cache_replylen; TYPE_1__ cache_addr; struct TYPE_11__* cache_next; } ;
typedef  TYPE_4__ SVCXPRT ;

/* Variables and functions */
 size_t CACHE_LOC (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  dupreq_lock ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freenetconfigent (struct netconfig*) ; 
 struct netconfig* getnetconfigent (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,char*) ; 
 struct svc_dg_data* su_data (TYPE_4__*) ; 
 char* taddr2uaddr (struct netconfig*,TYPE_5__*) ; 

__attribute__((used)) static int
cache_get(SVCXPRT *xprt, struct rpc_msg *msg, char **replyp, size_t *replylenp)
{
	u_int loc;
	cache_ptr ent;
	struct svc_dg_data *su = su_data(xprt);
	struct cl_cache *uc = (struct cl_cache *) su->su_cache;
#ifdef RPC_CACHE_DEBUG
	struct netconfig *nconf;
	char *uaddr;
#endif

	mutex_lock(&dupreq_lock);
	loc = CACHE_LOC(xprt, su->su_xid);
	for (ent = uc->uc_entries[loc]; ent != NULL; ent = ent->cache_next) {
		if (ent->cache_xid == su->su_xid &&
			ent->cache_proc == msg->rm_call.cb_proc &&
			ent->cache_vers == msg->rm_call.cb_vers &&
			ent->cache_prog == msg->rm_call.cb_prog &&
			ent->cache_addr.len == xprt->xp_rtaddr.len &&
			(memcmp(ent->cache_addr.buf, xprt->xp_rtaddr.buf,
				xprt->xp_rtaddr.len) == 0)) {
#ifdef RPC_CACHE_DEBUG
			if (nconf = getnetconfigent(xprt->xp_netid)) {
				uaddr = taddr2uaddr(nconf, &xprt->xp_rtaddr);
				freenetconfigent(nconf);
				printf(
	"cache entry found for xid=%x prog=%d vers=%d proc=%d for rmtaddr=%s\n",
					su->su_xid, msg->rm_call.cb_prog,
					msg->rm_call.cb_vers,
					msg->rm_call.cb_proc, uaddr);
				free(uaddr);
			}
#endif
			*replyp = ent->cache_reply;
			*replylenp = ent->cache_replylen;
			mutex_unlock(&dupreq_lock);
			return (1);
		}
	}
	/*
	 * Failed to find entry
	 * Remember a few things so we can do a set later
	 */
	uc->uc_proc = msg->rm_call.cb_proc;
	uc->uc_vers = msg->rm_call.cb_vers;
	uc->uc_prog = msg->rm_call.cb_prog;
	mutex_unlock(&dupreq_lock);
	return (0);
}