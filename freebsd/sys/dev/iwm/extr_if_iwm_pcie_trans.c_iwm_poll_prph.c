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
struct iwm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int iwm_read_prph (struct iwm_softc*,int) ; 

int
iwm_poll_prph(struct iwm_softc *sc, uint32_t addr, uint32_t bits, uint32_t mask,
    int timeout)
{
	do {
		if ((iwm_read_prph(sc, addr) & mask) == (bits & mask))
			return (0);
		DELAY(10);
		timeout -= 10;
	} while (timeout > 0);

	return (ETIMEDOUT);
}