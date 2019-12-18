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
 int /*<<< orphan*/  R92C_AGGLEN_LMT ; 
 int /*<<< orphan*/  R92C_AGGR_BREAK_TIME ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r92ce_init_ampdu(struct rtwn_softc *sc)
{

	/* Setup AMPDU aggregation. */
	rtwn_write_4(sc, R92C_AGGLEN_LMT, 0x99997631);	/* MCS7~0 */
	rtwn_write_1(sc, R92C_AGGR_BREAK_TIME, 0x16);
}