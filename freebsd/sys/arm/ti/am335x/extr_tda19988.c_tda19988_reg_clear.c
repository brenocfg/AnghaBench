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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tda19988_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tda19988_reg_read (struct tda19988_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda19988_reg_write (struct tda19988_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tda19988_reg_clear(struct tda19988_softc *sc, uint16_t addr, uint8_t flags)
{
	uint8_t data;

	tda19988_reg_read(sc, addr, &data);
	data &= ~flags;
	tda19988_reg_write(sc, addr, data);
}