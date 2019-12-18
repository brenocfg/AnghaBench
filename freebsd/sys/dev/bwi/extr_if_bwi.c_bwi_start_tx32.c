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
typedef  scalar_t__ uint32_t ;
struct bwi_softc {int dummy; } ;
struct bwi_desc32 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BWI_TX32_INDEX ; 
 int BWI_TX_NDESC ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bwi_softc*,scalar_t__,int) ; 

__attribute__((used)) static void
bwi_start_tx32(struct bwi_softc *sc, uint32_t tx_ctrl, int idx)
{
	idx = (idx + 1) % BWI_TX_NDESC;
	CSR_WRITE_4(sc, tx_ctrl + BWI_TX32_INDEX,
		    idx * sizeof(struct bwi_desc32));
}