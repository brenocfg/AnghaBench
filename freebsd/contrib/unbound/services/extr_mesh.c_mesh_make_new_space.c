#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname; } ;
struct TYPE_10__ {int /*<<< orphan*/  return_rcode; int /*<<< orphan*/ * return_msg; TYPE_3__ qinfo; } ;
struct TYPE_9__ {scalar_t__ count; } ;
struct mesh_state {scalar_t__ list_select; TYPE_5__ s; TYPE_4__ super_set; TYPE_2__* reply_list; } ;
struct mesh_area {scalar_t__ num_reply_states; scalar_t__ max_reply_states; int /*<<< orphan*/ * qbuf_bak; int /*<<< orphan*/  stats_jostled; int /*<<< orphan*/  jostle_max; TYPE_1__* env; struct mesh_state* jostle_first; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_7__ {int /*<<< orphan*/  start_time; } ;
struct TYPE_6__ {int /*<<< orphan*/  now_tv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mesh_jostle_list ; 
 int /*<<< orphan*/  mesh_state_delete (TYPE_5__*) ; 
 int /*<<< orphan*/  mesh_walk_supers (struct mesh_area*,struct mesh_state*) ; 
 int /*<<< orphan*/  sldns_buffer_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ timeval_smaller (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  timeval_subtract (struct timeval*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

int mesh_make_new_space(struct mesh_area* mesh, sldns_buffer* qbuf)
{
	struct mesh_state* m = mesh->jostle_first;
	/* free space is available */
	if(mesh->num_reply_states < mesh->max_reply_states)
		return 1;
	/* try to kick out a jostle-list item */
	if(m && m->reply_list && m->list_select == mesh_jostle_list) {
		/* how old is it? */
		struct timeval age;
		timeval_subtract(&age, mesh->env->now_tv, 
			&m->reply_list->start_time);
		if(timeval_smaller(&mesh->jostle_max, &age)) {
			/* its a goner */
			log_nametypeclass(VERB_ALGO, "query jostled out to "
				"make space for a new one",
				m->s.qinfo.qname, m->s.qinfo.qtype,
				m->s.qinfo.qclass);
			/* backup the query */
			if(qbuf) sldns_buffer_copy(mesh->qbuf_bak, qbuf);
			/* notify supers */
			if(m->super_set.count > 0) {
				verbose(VERB_ALGO, "notify supers of failure");
				m->s.return_msg = NULL;
				m->s.return_rcode = LDNS_RCODE_SERVFAIL;
				mesh_walk_supers(mesh, m);
			}
			mesh->stats_jostled ++;
			mesh_state_delete(&m->s);
			/* restore the query - note that the qinfo ptr to
			 * the querybuffer is then correct again. */
			if(qbuf) sldns_buffer_copy(qbuf, mesh->qbuf_bak);
			return 1;
		}
	}
	/* no space for new item */
	return 0;
}