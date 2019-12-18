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
 int /*<<< orphan*/  R92C_PBP ; 
 int R92C_PBP_512 ; 
 int /*<<< orphan*/  R92C_PBP_PSTX_M ; 
 int R92C_PBP_PSTX_S ; 
 scalar_t__ rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
r12a_set_page_size(struct rtwn_softc *sc)
{
	return (rtwn_setbits_1(sc, R92C_PBP, R92C_PBP_PSTX_M,
	    R92C_PBP_512 << R92C_PBP_PSTX_S) == 0);
}