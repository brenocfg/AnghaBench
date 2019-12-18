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
struct sfxge_txq {size_t ptr_mask; struct sfxge_tx_mapping* stmp; } ;
struct sfxge_tx_mapping {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ __predict_false (int) ; 

__attribute__((used)) static inline void
sfxge_next_stmp(struct sfxge_txq *txq, struct sfxge_tx_mapping **pstmp)
{
	KASSERT((*pstmp)->flags == 0, ("stmp flags are not 0"));
	if (__predict_false(*pstmp ==
			    &txq->stmp[txq->ptr_mask]))
		*pstmp = &txq->stmp[0];
	else
		(*pstmp)++;
}