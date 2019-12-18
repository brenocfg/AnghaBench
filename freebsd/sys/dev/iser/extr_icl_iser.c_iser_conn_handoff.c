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
struct iser_conn {scalar_t__ state; int handoff_done; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  min_posted_rx; } ;
struct icl_conn {int /*<<< orphan*/  ic_maxtags; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ISER_CONN_UP ; 
 int /*<<< orphan*/  ISER_ERR (char*,struct iser_conn*,scalar_t__) ; 
 struct iser_conn* icl_to_iser_conn (struct icl_conn*) ; 
 int iser_alloc_rx_descriptors (struct iser_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_free_rx_descriptors (struct iser_conn*) ; 
 int iser_post_recvm (struct iser_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
iser_conn_handoff(struct icl_conn *ic, int fd)
{
	struct iser_conn *iser_conn = icl_to_iser_conn(ic);
	int error = 0;

	sx_xlock(&iser_conn->state_mutex);
	if (iser_conn->state != ISER_CONN_UP) {
		error = EINVAL;
		ISER_ERR("iser_conn %p state is %d, teardown started\n",
			 iser_conn, iser_conn->state);
		goto out;
	}

	error = iser_alloc_rx_descriptors(iser_conn, ic->ic_maxtags);
	if (error)
		goto out;

	error = iser_post_recvm(iser_conn, iser_conn->min_posted_rx);
	if (error)
		goto post_error;

	iser_conn->handoff_done = true;

	sx_xunlock(&iser_conn->state_mutex);
	return (error);

post_error:
	iser_free_rx_descriptors(iser_conn);
out:
	sx_xunlock(&iser_conn->state_mutex);
	return (error);

}