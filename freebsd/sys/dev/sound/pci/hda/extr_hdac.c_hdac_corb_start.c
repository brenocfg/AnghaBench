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
struct hdac_softc {int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDAC_CORBCTL ; 
 int /*<<< orphan*/  HDAC_CORBCTL_CORBRUN ; 
 int /*<<< orphan*/  HDAC_READ_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDAC_WRITE_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdac_corb_start(struct hdac_softc *sc)
{
	uint32_t corbctl;

	corbctl = HDAC_READ_1(&sc->mem, HDAC_CORBCTL);
	corbctl |= HDAC_CORBCTL_CORBRUN;
	HDAC_WRITE_1(&sc->mem, HDAC_CORBCTL, corbctl);
}