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
struct dmar_unit {scalar_t__ inv_waitd_gen; scalar_t__ inv_waitd_seq_hw; } ;
struct dmar_qi_genseq {scalar_t__ gen; scalar_t__ seq; } ;

/* Variables and functions */

__attribute__((used)) static bool
dmar_qi_seq_processed(const struct dmar_unit *unit,
    const struct dmar_qi_genseq *pseq)
{

	return (pseq->gen < unit->inv_waitd_gen ||
	    (pseq->gen == unit->inv_waitd_gen &&
	     pseq->seq <= unit->inv_waitd_seq_hw));
}