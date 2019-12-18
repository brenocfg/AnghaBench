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
struct aw_ir_softc {scalar_t__ dcnt; } ;

/* Variables and functions */

__attribute__((used)) static void
aw_ir_buf_reset(struct aw_ir_softc *sc)
{

	sc->dcnt = 0;
}