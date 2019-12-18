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
struct tzic_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TZIC_PRIOMASK ; 
 int /*<<< orphan*/  tzic_write_4 (struct tzic_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
tzic_irq_eoi(struct tzic_softc *sc)
{

	tzic_write_4(sc, TZIC_PRIOMASK, 0xff);
}