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
struct pfr_ktableworkq {int dummy; } ;
struct pfr_ktable {int dummy; } ;

/* Variables and functions */
 struct pfr_ktable* SLIST_FIRST (struct pfr_ktableworkq*) ; 
 struct pfr_ktable* SLIST_NEXT (struct pfr_ktable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_destroy_ktable (struct pfr_ktable*,int) ; 
 int /*<<< orphan*/  pfrkt_workq ; 

__attribute__((used)) static void
pfr_destroy_ktables(struct pfr_ktableworkq *workq, int flushaddr)
{
	struct pfr_ktable	*p, *q;

	for (p = SLIST_FIRST(workq); p; p = q) {
		q = SLIST_NEXT(p, pfrkt_workq);
		pfr_destroy_ktable(p, flushaddr);
	}
}