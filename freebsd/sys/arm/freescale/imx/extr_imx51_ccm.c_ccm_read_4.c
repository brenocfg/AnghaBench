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
typedef  int /*<<< orphan*/  uint32_t ;
struct imxccm_softc {int /*<<< orphan*/  ccmregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline uint32_t
ccm_read_4(struct imxccm_softc *sc, int reg)
{

	return (bus_read_4(sc->ccmregs, reg));
}