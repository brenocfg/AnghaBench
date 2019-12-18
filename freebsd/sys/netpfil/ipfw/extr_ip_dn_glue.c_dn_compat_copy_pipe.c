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
struct TYPE_2__ {int flags; } ;
struct dn_schk {scalar_t__ siht; TYPE_1__ sch; } ;
struct dn_pipe8 {int dummy; } ;
struct dn_flow_queue8 {int dummy; } ;
struct copy_args {int end; int* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int,int) ; 
 int DN_HAVE_MASK ; 
 int /*<<< orphan*/  dn_c_copy_pipe (struct dn_schk*,struct copy_args*,int) ; 
 int /*<<< orphan*/  dn_c_copy_q (scalar_t__,struct copy_args*) ; 
 int dn_ht_entries (scalar_t__) ; 
 int /*<<< orphan*/  dn_ht_scan (scalar_t__,int /*<<< orphan*/  (*) (scalar_t__,struct copy_args*),struct copy_args*) ; 

int
dn_compat_copy_pipe(struct copy_args *a, void *_o)
{
	int have = a->end - *a->start;
	int need = 0;
	int pipe_size = sizeof(struct dn_pipe8);
	int queue_size = sizeof(struct dn_flow_queue8);
	int n_queue = 0; /* number of queues */

	struct dn_schk *s = (struct dn_schk *)_o;
	/* calculate needed space:
	 * - struct dn_pipe
	 * - if there are instances, dn_queue * n_instances
	 */
	n_queue = (s->sch.flags & DN_HAVE_MASK ? dn_ht_entries(s->siht) :
						(s->siht ? 1 : 0));
	need = pipe_size + queue_size * n_queue;
	if (have < need) {
		D("have %d < need %d", have, need);
		return 1;
	}
	/* copy pipe */
	dn_c_copy_pipe(s, a, n_queue);

	/* copy queues */
	if (s->sch.flags & DN_HAVE_MASK)
		dn_ht_scan(s->siht, dn_c_copy_q, a);
	else if (s->siht)
		dn_c_copy_q(s->siht, a);
	return 0;
}