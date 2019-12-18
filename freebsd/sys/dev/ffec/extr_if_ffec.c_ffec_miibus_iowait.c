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
struct ffec_softc {int dummy; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int FEC_IER_MII ; 
 int /*<<< orphan*/  FEC_IER_REG ; 
 int RD4 (struct ffec_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
ffec_miibus_iowait(struct ffec_softc *sc)
{
	uint32_t timeout;

	for (timeout = 10000; timeout != 0; --timeout)
		if (RD4(sc, FEC_IER_REG) & FEC_IER_MII)
			return (true);

	return (false);
}