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
struct svc_callout {struct svc_callout* sc_netid; int /*<<< orphan*/ * sc_next; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;

/* Variables and functions */
 int /*<<< orphan*/  mem_free (struct svc_callout*,int) ; 
 int /*<<< orphan*/  rpcb_unset (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wrlock (int /*<<< orphan*/ *) ; 
 struct svc_callout* svc_find (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct svc_callout**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svc_head ; 
 int /*<<< orphan*/  svc_lock ; 

void
svc_unreg(const rpcprog_t prog, const rpcvers_t vers)
{
	struct svc_callout *prev;
	struct svc_callout *s;

	/* unregister the information anyway */
	(void) rpcb_unset(prog, vers, NULL);
	rwlock_wrlock(&svc_lock);
	while ((s = svc_find(prog, vers, &prev, NULL)) != NULL) {
		if (prev == NULL) {
			svc_head = s->sc_next;
		} else {
			prev->sc_next = s->sc_next;
		}
		s->sc_next = NULL;
		if (s->sc_netid)
			mem_free(s->sc_netid, sizeof (s->sc_netid) + 1);
		mem_free(s, sizeof (struct svc_callout));
	}
	rwlock_unlock(&svc_lock);
}