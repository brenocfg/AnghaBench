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
struct waiting_tcp {void* cb_arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ next_waiting; scalar_t__ pkt; struct outside_network* outnet; } ;
struct pending_tcp {struct pending_tcp* next_free; int /*<<< orphan*/ * query; TYPE_1__* c; } ;
struct outside_network {struct pending_tcp* tcp_free; } ;
typedef  int /*<<< orphan*/  (* comm_point_callback_type ) (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
struct TYPE_2__ {int /*<<< orphan*/ * ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_TIMEOUT ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comm_point_close (TYPE_1__*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_pending_tcp (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_free_buffer (struct outside_network*) ; 
 int /*<<< orphan*/  waiting_list_remove (struct outside_network*,struct waiting_tcp*) ; 
 int /*<<< orphan*/  waiting_tcp_delete (struct waiting_tcp*) ; 

void
outnet_tcptimer(void* arg)
{
	struct waiting_tcp* w = (struct waiting_tcp*)arg;
	struct outside_network* outnet = w->outnet;
	comm_point_callback_type* cb;
	void* cb_arg;
	if(w->pkt) {
		/* it is on the waiting list */
		waiting_list_remove(outnet, w);
	} else {
		/* it was in use */
		struct pending_tcp* pend=(struct pending_tcp*)w->next_waiting;
		if(pend->c->ssl) {
#ifdef HAVE_SSL
			SSL_shutdown(pend->c->ssl);
			SSL_free(pend->c->ssl);
			pend->c->ssl = NULL;
#endif
		}
		comm_point_close(pend->c);
		pend->query = NULL;
		pend->next_free = outnet->tcp_free;
		outnet->tcp_free = pend;
	}
	cb = w->cb;
	cb_arg = w->cb_arg;
	waiting_tcp_delete(w);
	fptr_ok(fptr_whitelist_pending_tcp(cb));
	(void)(*cb)(NULL, cb_arg, NETEVENT_TIMEOUT, NULL);
	use_free_buffer(outnet);
}