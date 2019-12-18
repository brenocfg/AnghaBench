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
typedef  int /*<<< orphan*/  u16 ;
struct ixl_pf_qtag {int dummy; } ;
struct ixl_pf {int dummy; } ;

/* Variables and functions */
 int ixl_disable_rx_ring (struct ixl_pf*,struct ixl_pf_qtag*,int /*<<< orphan*/ ) ; 
 int ixl_disable_tx_ring (struct ixl_pf*,struct ixl_pf_qtag*,int /*<<< orphan*/ ) ; 

int
ixl_disable_ring(struct ixl_pf *pf, struct ixl_pf_qtag *qtag, u16 vsi_qidx)
{
	int error = 0;

	error = ixl_disable_tx_ring(pf, qtag, vsi_qidx);
	/* Called function already prints error message */
	if (error)
		return (error);
	error = ixl_disable_rx_ring(pf, qtag, vsi_qidx);
	return (error);
}