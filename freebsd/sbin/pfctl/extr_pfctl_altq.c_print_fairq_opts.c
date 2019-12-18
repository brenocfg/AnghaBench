#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fairq_opts {int flags; scalar_t__ lssc_m2; scalar_t__ lssc_d; int /*<<< orphan*/  lssc_m1; } ;
struct TYPE_4__ {struct fairq_opts fairq_opts; } ;
struct pf_altq {scalar_t__ bandwidth; TYPE_1__ pq_u; } ;
struct node_fairq_sc {int dummy; } ;
struct TYPE_5__ {struct node_fairq_sc linkshare; } ;
struct TYPE_6__ {TYPE_2__ fairq_opts; } ;
struct node_queue_opt {TYPE_3__ data; } ;

/* Variables and functions */
 int FARF_CLEARDSCP ; 
 int FARF_CODEL ; 
 int FARF_DEFAULTCLASS ; 
 int FARF_ECN ; 
 int FARF_RED ; 
 int FARF_RIO ; 
 int /*<<< orphan*/  print_fairq_sc (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct node_fairq_sc const*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
print_fairq_opts(const struct pf_altq *a, const struct node_queue_opt *qopts)
{
	const struct fairq_opts		*opts;
	const struct node_fairq_sc	*loc_lssc;

	opts = &a->pq_u.fairq_opts;
	if (qopts == NULL)
		loc_lssc = NULL;
	else
		loc_lssc = &qopts->data.fairq_opts.linkshare;

	if (opts->flags ||
	    (opts->lssc_m2 != 0 && (opts->lssc_m2 != a->bandwidth ||
	    opts->lssc_d != 0))) {
		printf("fairq(");
		if (opts->flags & FARF_RED)
			printf(" red");
		if (opts->flags & FARF_ECN)
			printf(" ecn");
		if (opts->flags & FARF_RIO)
			printf(" rio");
		if (opts->flags & FARF_CODEL)
			printf(" codel");
		if (opts->flags & FARF_CLEARDSCP)
			printf(" cleardscp");
		if (opts->flags & FARF_DEFAULTCLASS)
			printf(" default");
		if (opts->lssc_m2 != 0 && (opts->lssc_m2 != a->bandwidth ||
		    opts->lssc_d != 0))
			print_fairq_sc("linkshare", opts->lssc_m1, opts->lssc_d,
			    opts->lssc_m2, loc_lssc);
		printf(" ) ");

		return (1);
	} else
		return (0);
}