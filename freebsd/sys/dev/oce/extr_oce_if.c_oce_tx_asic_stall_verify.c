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
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IS_QNQ_OR_UMC (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ is_be3_a1 (int /*<<< orphan*/ ) ; 
 scalar_t__ oce_check_ipv6_ext_hdr (struct mbuf*) ; 

__attribute__((used)) static int 
oce_tx_asic_stall_verify(POCE_SOFTC sc, struct mbuf *m)
{
	if(is_be3_a1(sc) && IS_QNQ_OR_UMC(sc) && \
			oce_check_ipv6_ext_hdr(m)) {
		return TRUE;
	}
	return FALSE;
}