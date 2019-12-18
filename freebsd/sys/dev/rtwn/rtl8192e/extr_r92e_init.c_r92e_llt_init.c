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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  R92C_AUTO_LLT ; 
 int R92C_AUTO_LLT_INIT ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 
 int rtwn_read_4 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int rtwn_setbits_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
r92e_llt_init(struct rtwn_softc *sc)
{
	int ntries, error;

	error = rtwn_setbits_4(sc, R92C_AUTO_LLT, 0, R92C_AUTO_LLT_INIT);
	if (error != 0)
		return (error);
	for (ntries = 0; ntries < 1000; ntries++) {
		if (!(rtwn_read_4(sc, R92C_AUTO_LLT) & R92C_AUTO_LLT_INIT))
			return (0);
		rtwn_delay(sc, 1);
	}
	return (ETIMEDOUT);
}