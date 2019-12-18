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
typedef  int u_int ;
struct sge_eq {int sidx; } ;
struct mp_ring {struct sge_eq* cookie; } ;

/* Variables and functions */
 int total_available_tx_desc (struct sge_eq*) ; 

__attribute__((used)) static u_int
can_resume_eth_tx(struct mp_ring *r)
{
	struct sge_eq *eq = r->cookie;

	return (total_available_tx_desc(eq) > eq->sidx / 8);
}