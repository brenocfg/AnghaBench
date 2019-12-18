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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct serviced_query {struct serviced_query* cblist; struct serviced_query* next; void* cb_arg; int /*<<< orphan*/ * cb; struct serviced_query* zone; struct serviced_query* qbuf; } ;
struct service_callback {struct service_callback* cblist; struct service_callback* next; void* cb_arg; int /*<<< orphan*/ * cb; struct service_callback* zone; struct service_callback* qbuf; } ;
struct query_info {scalar_t__ qtype; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct outside_network {int /*<<< orphan*/  serviced; scalar_t__ do_udp; } ;
struct module_qstate {int /*<<< orphan*/  edns_opts_back_out; int /*<<< orphan*/  region; } ;
struct module_env {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  comm_point_callback_type ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct serviced_query*) ; 
 int /*<<< orphan*/  inplace_cb_query_call (struct module_env*,struct query_info*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,struct module_qstate*,int /*<<< orphan*/ ) ; 
 struct serviced_query* lookup_serviced (struct outside_network*,int /*<<< orphan*/ *,int,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ ,struct serviced_query*) ; 
 struct serviced_query* serviced_create (struct outside_network*,int /*<<< orphan*/ *,int,int,int,int,int,char*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serviced_gen_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serviced_tcp_send (struct serviced_query*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serviced_udp_send (struct serviced_query*,int /*<<< orphan*/ *) ; 

struct serviced_query* 
outnet_serviced_query(struct outside_network* outnet,
	struct query_info* qinfo, uint16_t flags, int dnssec, int want_dnssec,
	int nocaps, int tcp_upstream, int ssl_upstream, char* tls_auth_name,
	struct sockaddr_storage* addr, socklen_t addrlen, uint8_t* zone,
	size_t zonelen, struct module_qstate* qstate,
	comm_point_callback_type* callback, void* callback_arg, sldns_buffer* buff,
	struct module_env* env)
{
	struct serviced_query* sq;
	struct service_callback* cb;
	if(!inplace_cb_query_call(env, qinfo, flags, addr, addrlen, zone, zonelen,
		qstate, qstate->region))
			return NULL;
	serviced_gen_query(buff, qinfo->qname, qinfo->qname_len, qinfo->qtype,
		qinfo->qclass, flags);
	sq = lookup_serviced(outnet, buff, dnssec, addr, addrlen,
		qstate->edns_opts_back_out);
	/* duplicate entries are included in the callback list, because
	 * there is a counterpart registration by our caller that needs to
	 * be doubly-removed (with callbacks perhaps). */
	if(!(cb = (struct service_callback*)malloc(sizeof(*cb))))
		return NULL;
	if(!sq) {
		/* make new serviced query entry */
		sq = serviced_create(outnet, buff, dnssec, want_dnssec, nocaps,
			tcp_upstream, ssl_upstream, tls_auth_name, addr,
			addrlen, zone, zonelen, (int)qinfo->qtype,
			qstate->edns_opts_back_out);
		if(!sq) {
			free(cb);
			return NULL;
		}
		/* perform first network action */
		if(outnet->do_udp && !(tcp_upstream || ssl_upstream)) {
			if(!serviced_udp_send(sq, buff)) {
				(void)rbtree_delete(outnet->serviced, sq);
				free(sq->qbuf);
				free(sq->zone);
				free(sq);
				free(cb);
				return NULL;
			}
		} else {
			if(!serviced_tcp_send(sq, buff)) {
				(void)rbtree_delete(outnet->serviced, sq);
				free(sq->qbuf);
				free(sq->zone);
				free(sq);
				free(cb);
				return NULL;
			}
		}
	}
	/* add callback to list of callbacks */
	cb->cb = callback;
	cb->cb_arg = callback_arg;
	cb->next = sq->cblist;
	sq->cblist = cb;
	return sq;
}