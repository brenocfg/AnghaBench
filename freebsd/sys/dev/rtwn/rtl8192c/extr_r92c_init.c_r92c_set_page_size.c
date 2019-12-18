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
 int /*<<< orphan*/  R92C_PBP_128 ; 
 int /*<<< orphan*/  R92C_PBP_PSRX ; 
 int /*<<< orphan*/  R92C_PBP_PSTX ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

int
r92c_set_page_size(struct rtwn_softc *sc)
{
	return (rtwn_write_1(sc, R92C_PBP, SM(R92C_PBP_PSRX, R92C_PBP_128) |
	    SM(R92C_PBP_PSTX, R92C_PBP_128)) == 0);
}