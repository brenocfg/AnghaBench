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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int* key; } ;
struct ub_result {int querynum; int async; int qtype; int qclass; TYPE_1__ node; struct ub_result* res; int /*<<< orphan*/  qname; } ;
struct ub_ctx {int /*<<< orphan*/  queries; int /*<<< orphan*/  num_async; } ;
struct ctx_query {int querynum; int async; int qtype; int qclass; TYPE_1__ node; struct ctx_query* res; int /*<<< orphan*/  qname; } ;

/* Variables and functions */
 scalar_t__ UB_LIBCMD_NEWQUERY ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct ub_result*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ sldns_read_uint32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char*) ; 

struct ctx_query* 
context_deserialize_new_query(struct ub_ctx* ctx, uint8_t* p, uint32_t len)
{
	struct ctx_query* q = (struct ctx_query*)calloc(1, sizeof(*q));
	if(!q) return NULL;
	if(len < 4*sizeof(uint32_t)+1) {
		free(q);
		return NULL;
	}
	log_assert( sldns_read_uint32(p) == UB_LIBCMD_NEWQUERY);
	q->querynum = (int)sldns_read_uint32(p+sizeof(uint32_t));
	q->node.key = &q->querynum;
	q->async = 1;
	q->res = (struct ub_result*)calloc(1, sizeof(*q->res));
	if(!q->res) {
		free(q);
		return NULL;
	}
	q->res->qtype = (int)sldns_read_uint32(p+2*sizeof(uint32_t));
	q->res->qclass = (int)sldns_read_uint32(p+3*sizeof(uint32_t));
	q->res->qname = strdup((char*)(p+4*sizeof(uint32_t)));
	if(!q->res->qname) {
		free(q->res);
		free(q);
		return NULL;
	}

	/** add to query list */
	ctx->num_async++;
	(void)rbtree_insert(&ctx->queries, &q->node);
	return q;
}