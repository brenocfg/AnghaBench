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
struct priq_opts {int flags; } ;
struct TYPE_2__ {struct priq_opts priq_opts; } ;
struct pf_altq {TYPE_1__ pq_u; } ;

/* Variables and functions */
 int PRCF_CLEARDSCP ; 
 int PRCF_CODEL ; 
 int PRCF_DEFAULTCLASS ; 
 int PRCF_ECN ; 
 int PRCF_RED ; 
 int PRCF_RIO ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
print_priq_opts(const struct pf_altq *a)
{
	const struct priq_opts	*opts;

	opts = &a->pq_u.priq_opts;

	if (opts->flags) {
		printf("priq(");
		if (opts->flags & PRCF_RED)
			printf(" red");
		if (opts->flags & PRCF_ECN)
			printf(" ecn");
		if (opts->flags & PRCF_RIO)
			printf(" rio");
		if (opts->flags & PRCF_CODEL)
			printf(" codel");
		if (opts->flags & PRCF_CLEARDSCP)
			printf(" cleardscp");
		if (opts->flags & PRCF_DEFAULTCLASS)
			printf(" default");
		printf(" ) ");

		return (1);
	} else
		return (0);
}