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
typedef  int /*<<< orphan*/  u_int ;
struct sge_rspq {int /*<<< orphan*/  cntxt_id; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_RSPQ_CREDIT_RETURN ; 
 int V_CREDITS (int /*<<< orphan*/ ) ; 
 int V_RSPQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
refill_rspq(adapter_t *sc, const struct sge_rspq *q, u_int credits)
{

	/* mbufs are allocated on demand when a rspq entry is processed. */
	t3_write_reg(sc, A_SG_RSPQ_CREDIT_RETURN,
		     V_RSPQ(q->cntxt_id) | V_CREDITS(credits));
}