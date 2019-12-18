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
struct ural_softc {int dummy; } ;

/* Variables and functions */
 int RAL_ENABLE_TSF ; 
 int RAL_ENABLE_TSF_SYNC (int) ; 
 int /*<<< orphan*/  RAL_TXRX_CSR19 ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ural_enable_tsf(struct ural_softc *sc)
{
	/* first, disable TSF synchronization */
	ural_write(sc, RAL_TXRX_CSR19, 0);
	ural_write(sc, RAL_TXRX_CSR19, RAL_ENABLE_TSF | RAL_ENABLE_TSF_SYNC(2));
}