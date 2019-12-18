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
struct rsocket {scalar_t__ udp_sock; scalar_t__ index; scalar_t__ epfd; int /*<<< orphan*/  slock; int /*<<< orphan*/  rlock; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  cq_wait_lock; int /*<<< orphan*/  map_lock; int /*<<< orphan*/  dest_map; struct rsocket* sbuf; struct ds_qp* qp_list; struct rsocket* dmsg; } ;
struct ds_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  ds_free_qp (struct ds_qp*) ; 
 int /*<<< orphan*/  ds_remove_qp (struct rsocket*,struct ds_qp*) ; 
 int /*<<< orphan*/  fastlock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct rsocket*) ; 
 int /*<<< orphan*/  rs_remove (struct rsocket*) ; 
 int /*<<< orphan*/  tdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct rsocket*)) ; 

__attribute__((used)) static void ds_free(struct rsocket *rs)
{
	struct ds_qp *qp;

	if (rs->udp_sock >= 0)
		close(rs->udp_sock);

	if (rs->index >= 0)
		rs_remove(rs);

	if (rs->dmsg)
		free(rs->dmsg);

	while ((qp = rs->qp_list)) {
		ds_remove_qp(rs, qp);
		ds_free_qp(qp);
	}

	if (rs->epfd >= 0)
		close(rs->epfd);

	if (rs->sbuf)
		free(rs->sbuf);

	tdestroy(rs->dest_map, free);
	fastlock_destroy(&rs->map_lock);
	fastlock_destroy(&rs->cq_wait_lock);
	fastlock_destroy(&rs->cq_lock);
	fastlock_destroy(&rs->rlock);
	fastlock_destroy(&rs->slock);
	free(rs);
}