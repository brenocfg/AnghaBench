#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct svc_callout {struct svc_callout* sc_netid; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
struct TYPE_4__ {int /*<<< orphan*/  sp_lock; int /*<<< orphan*/  sp_callouts; } ;
typedef  TYPE_1__ SVCPOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct svc_callout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_free (struct svc_callout*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcb_unset (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_link ; 
 struct svc_callout* svc_find (TYPE_1__*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

void
svc_unreg(SVCPOOL *pool, const rpcprog_t prog, const rpcvers_t vers)
{
	struct svc_callout *s;

	/* unregister the information anyway */
	(void) rpcb_unset(prog, vers, NULL);
	mtx_lock(&pool->sp_lock);
	while ((s = svc_find(pool, prog, vers, NULL)) != NULL) {
		TAILQ_REMOVE(&pool->sp_callouts, s, sc_link);
		if (s->sc_netid)
			mem_free(s->sc_netid, sizeof (s->sc_netid) + 1);
		mem_free(s, sizeof (struct svc_callout));
	}
	mtx_unlock(&pool->sp_lock);
}