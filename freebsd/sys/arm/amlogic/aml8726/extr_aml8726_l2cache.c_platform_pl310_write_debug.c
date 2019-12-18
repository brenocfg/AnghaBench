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
struct pl310_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PL310_DEBUG_CTRL ; 
 int /*<<< orphan*/  pl310_write4 (struct pl310_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
platform_pl310_write_debug(struct pl310_softc *sc, uint32_t val)
{

	pl310_write4(sc, PL310_DEBUG_CTRL, val);
}