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
typedef  int uint32_t ;
struct bcm_lintc_softc {int dummy; } ;

/* Variables and functions */
 int bcm_lintc_read_4 (struct bcm_lintc_softc*,int) ; 
 int /*<<< orphan*/  bcm_lintc_write_4 (struct bcm_lintc_softc*,int,int) ; 

__attribute__((used)) static inline void
bcm_lintc_rwreg_set(struct bcm_lintc_softc *sc, uint32_t reg,
    uint32_t mask)
{

	bcm_lintc_write_4(sc, reg, bcm_lintc_read_4(sc, reg) | mask);
}