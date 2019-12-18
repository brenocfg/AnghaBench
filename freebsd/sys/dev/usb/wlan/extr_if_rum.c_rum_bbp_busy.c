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
struct rum_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int RT2573_BBP_BUSY ; 
 int /*<<< orphan*/  RT2573_PHY_CSR3 ; 
 int hz ; 
 scalar_t__ rum_pause (struct rum_softc*,int) ; 
 int rum_read (struct rum_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rum_bbp_busy(struct rum_softc *sc)
{
	int ntries;

	for (ntries = 0; ntries < 100; ntries++) {
		if (!(rum_read(sc, RT2573_PHY_CSR3) & RT2573_BBP_BUSY))
			break;
		if (rum_pause(sc, hz / 100))
			break;
	}
	if (ntries == 100)
		return (ETIMEDOUT);

	return (0);
}