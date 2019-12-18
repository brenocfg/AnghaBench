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
struct hn_txdesc {int flags; int /*<<< orphan*/  agg_list; } ;

/* Variables and functions */
 int HN_TXD_FLAG_ONAGG ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct hn_txdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_link ; 

__attribute__((used)) static __inline void
hn_txdesc_agg(struct hn_txdesc *agg_txd, struct hn_txdesc *txd)
{

	KASSERT((agg_txd->flags & HN_TXD_FLAG_ONAGG) == 0,
	    ("recursive aggregation on aggregating txdesc"));

	KASSERT((txd->flags & HN_TXD_FLAG_ONAGG) == 0,
	    ("already aggregated"));
	KASSERT(STAILQ_EMPTY(&txd->agg_list),
	    ("recursive aggregation on to-be-aggregated txdesc"));

	txd->flags |= HN_TXD_FLAG_ONAGG;
	STAILQ_INSERT_TAIL(&agg_txd->agg_list, txd, agg_link);
}