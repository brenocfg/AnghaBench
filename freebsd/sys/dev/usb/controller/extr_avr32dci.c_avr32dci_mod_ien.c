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
struct avr32dci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_IEN ; 
 int /*<<< orphan*/  AVR32_READ_4 (struct avr32dci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVR32_WRITE_4 (struct avr32dci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
avr32dci_mod_ien(struct avr32dci_softc *sc, uint32_t set, uint32_t clear)
{
	uint32_t temp;

	temp = AVR32_READ_4(sc, AVR32_IEN);
	temp |= set;
	temp &= ~clear;
	AVR32_WRITE_4(sc, AVR32_IEN, temp);
}