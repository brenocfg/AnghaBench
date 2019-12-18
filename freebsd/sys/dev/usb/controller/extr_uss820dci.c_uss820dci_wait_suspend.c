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
typedef  scalar_t__ uint8_t ;
struct uss820dci_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ USS820_READ_1 (struct uss820dci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USS820_SCR ; 
 int /*<<< orphan*/  USS820_SCRATCH ; 
 scalar_t__ USS820_SCRATCH_IE_RESUME ; 
 scalar_t__ USS820_SCR_IE_SUSP ; 
 int /*<<< orphan*/  USS820_WRITE_1 (struct uss820dci_softc*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
uss820dci_wait_suspend(struct uss820dci_softc *sc, uint8_t on)
{
	uint8_t scr;
	uint8_t scratch;

	scr = USS820_READ_1(sc, USS820_SCR);
	scratch = USS820_READ_1(sc, USS820_SCRATCH);

	if (on) {
		scr |= USS820_SCR_IE_SUSP;
		scratch &= ~USS820_SCRATCH_IE_RESUME;
	} else {
		scr &= ~USS820_SCR_IE_SUSP;
		scratch |= USS820_SCRATCH_IE_RESUME;
	}

	USS820_WRITE_1(sc, USS820_SCR, scr);
	USS820_WRITE_1(sc, USS820_SCRATCH, scratch);
}