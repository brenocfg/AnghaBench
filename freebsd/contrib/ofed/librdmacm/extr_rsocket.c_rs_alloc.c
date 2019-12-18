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
struct rsocket {int type; int index; int udp_sock; int epfd; int /*<<< orphan*/  iomap_queue; int /*<<< orphan*/  iomap_list; int /*<<< orphan*/  map_lock; int /*<<< orphan*/  cq_wait_lock; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  rlock; int /*<<< orphan*/  slock; int /*<<< orphan*/  target_iomap_size; int /*<<< orphan*/  ctrl_max_seqno; int /*<<< orphan*/  rq_size; int /*<<< orphan*/  sq_size; int /*<<< orphan*/  sq_inline; int /*<<< orphan*/  rbuf_size; int /*<<< orphan*/  sbuf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS_QP_CTRL_SIZE ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 struct rsocket* calloc (int,int) ; 
 int /*<<< orphan*/  def_inline ; 
 int /*<<< orphan*/  def_iomap_size ; 
 int /*<<< orphan*/  def_mem ; 
 int /*<<< orphan*/  def_rqsize ; 
 int /*<<< orphan*/  def_sqsize ; 
 int /*<<< orphan*/  def_wmem ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rsocket *rs_alloc(struct rsocket *inherited_rs, int type)
{
	struct rsocket *rs;

	rs = calloc(1, sizeof(*rs));
	if (!rs)
		return NULL;

	rs->type = type;
	rs->index = -1;
	if (type == SOCK_DGRAM) {
		rs->udp_sock = -1;
		rs->epfd = -1;
	}

	if (inherited_rs) {
		rs->sbuf_size = inherited_rs->sbuf_size;
		rs->rbuf_size = inherited_rs->rbuf_size;
		rs->sq_inline = inherited_rs->sq_inline;
		rs->sq_size = inherited_rs->sq_size;
		rs->rq_size = inherited_rs->rq_size;
		if (type == SOCK_STREAM) {
			rs->ctrl_max_seqno = inherited_rs->ctrl_max_seqno;
			rs->target_iomap_size = inherited_rs->target_iomap_size;
		}
	} else {
		rs->sbuf_size = def_wmem;
		rs->rbuf_size = def_mem;
		rs->sq_inline = def_inline;
		rs->sq_size = def_sqsize;
		rs->rq_size = def_rqsize;
		if (type == SOCK_STREAM) {
			rs->ctrl_max_seqno = RS_QP_CTRL_SIZE;
			rs->target_iomap_size = def_iomap_size;
		}
	}
	fastlock_init(&rs->slock);
	fastlock_init(&rs->rlock);
	fastlock_init(&rs->cq_lock);
	fastlock_init(&rs->cq_wait_lock);
	fastlock_init(&rs->map_lock);
	dlist_init(&rs->iomap_list);
	dlist_init(&rs->iomap_queue);
	return rs;
}