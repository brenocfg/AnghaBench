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
typedef  int uint8_t ;
struct saf1761_otg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOTG_ADDRESS ; 
 int SOTG_ADDRESS_ENABLE ; 

__attribute__((used)) static void
saf1761_otg_set_address(struct saf1761_otg_softc *sc, uint8_t addr)
{
	DPRINTFN(5, "addr=%d\n", addr);

	SAF1761_WRITE_LE_4(sc, SOTG_ADDRESS, addr | SOTG_ADDRESS_ENABLE);
}