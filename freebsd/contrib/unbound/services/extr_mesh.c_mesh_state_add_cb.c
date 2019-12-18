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
typedef  void* uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  region; } ;
struct mesh_state {struct mesh_cb* cb_list; TYPE_1__ s; } ;
struct edns_data {scalar_t__ opt_list; } ;
struct mesh_cb {struct mesh_cb* next; void* qflags; void* qid; struct edns_data edns; void* cb_arg; int /*<<< orphan*/  cb; int /*<<< orphan*/ * buf; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  mesh_cb_func_type ;

/* Variables and functions */
 scalar_t__ edns_opt_copy_region (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_mesh_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 struct mesh_cb* regional_alloc (int /*<<< orphan*/ ,int) ; 

int mesh_state_add_cb(struct mesh_state* s, struct edns_data* edns,
        sldns_buffer* buf, mesh_cb_func_type cb, void* cb_arg,
	uint16_t qid, uint16_t qflags)
{
	struct mesh_cb* r = regional_alloc(s->s.region, 
		sizeof(struct mesh_cb));
	if(!r)
		return 0;
	r->buf = buf;
	log_assert(fptr_whitelist_mesh_cb(cb)); /* early failure ifmissing*/
	r->cb = cb;
	r->cb_arg = cb_arg;
	r->edns = *edns;
	if(edns->opt_list) {
		r->edns.opt_list = edns_opt_copy_region(edns->opt_list,
			s->s.region);
		if(!r->edns.opt_list)
			return 0;
	}
	r->qid = qid;
	r->qflags = qflags;
	r->next = s->cb_list;
	s->cb_list = r;
	return 1;

}