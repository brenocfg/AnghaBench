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
struct codel_opts {int target; int interval; scalar_t__ ecn; } ;
struct TYPE_2__ {struct codel_opts codel_opts; } ;
struct pf_altq {TYPE_1__ pq_u; } ;
struct node_queue_opt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
print_codel_opts(const struct pf_altq *a, const struct node_queue_opt *qopts)
{
	const struct codel_opts *opts;

	opts = &a->pq_u.codel_opts;
	if (opts->target || opts->interval || opts->ecn) {
		printf("codel(");
		if (opts->target)
			printf(" target %d", opts->target);
		if (opts->interval)
			printf(" interval %d", opts->interval);
		if (opts->ecn)
			printf("ecn");
		printf(" ) ");

		return (1);
	}

	return (0);
}