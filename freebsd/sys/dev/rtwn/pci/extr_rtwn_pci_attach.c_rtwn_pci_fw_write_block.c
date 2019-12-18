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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtwn_pci_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
rtwn_pci_fw_write_block(struct rtwn_softc *sc, const uint8_t *buf,
    uint16_t reg, int mlen)
{
	int i;

	for (i = 0; i < mlen; i++)
		rtwn_pci_write_1(sc, reg++, buf[i]);

	/* NB: cannot fail */
	return (0);
}