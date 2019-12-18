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
typedef  int /*<<< orphan*/  uint32_t ;
struct nct_softc {int /*<<< orphan*/  dev_f; } ;

/* Variables and functions */
 int NCT_PIN_BIT (int /*<<< orphan*/ ) ; 
 int nct_outcfg_addr (int /*<<< orphan*/ ) ; 
 int superio_read (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
nct_pin_is_opendrain(struct nct_softc *sc, uint32_t pin_num)
{
	uint8_t reg;
	uint8_t outcfg;

	reg = nct_outcfg_addr(pin_num);
	outcfg = superio_read(sc->dev_f, reg);
	return (outcfg & NCT_PIN_BIT(pin_num));
}