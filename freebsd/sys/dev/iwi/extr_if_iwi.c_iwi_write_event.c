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
struct iwi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWI_MEM_EEPROM_EVENT ; 
 int /*<<< orphan*/  MEM_WRITE_4 (struct iwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwi_write_event(struct iwi_softc *sc, uint32_t v)
{
	MEM_WRITE_4(sc, IWI_MEM_EEPROM_EVENT, v);
}