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
typedef  int uint32_t ;
struct cqspi_softc {int dummy; } ;

/* Variables and functions */
 int CFG_IDLE ; 
 int /*<<< orphan*/  CQSPI_CFG ; 
 int READ4 (struct cqspi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cqspi_wait_idle(struct cqspi_softc *sc)
{
	uint32_t reg;

	do {
		reg = READ4(sc, CQSPI_CFG);
		if (reg & CFG_IDLE) {
			break;
		}
	} while (1);

	return (0);
}