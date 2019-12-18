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
struct mgb_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ mgb_intr_test (struct mgb_softc*) ; 

__attribute__((used)) static int
mgb_attach_post(if_ctx_t ctx)
{
	struct mgb_softc *sc;

	sc = iflib_get_softc(ctx);

	device_printf(sc->dev, "Interrupt test: %s\n",
	    (mgb_intr_test(sc) ? "PASS" : "FAIL"));

	return (0);
}