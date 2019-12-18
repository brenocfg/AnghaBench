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
 int /*<<< orphan*/  R92C_USTIME_EDCA ; 
 int /*<<< orphan*/  R92C_USTIME_TSF ; 
 int /*<<< orphan*/  r92c_init_edca (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r12a_init_edca(struct rtwn_softc *sc)
{
	r92c_init_edca(sc);

	/* 80 MHz clock */
	rtwn_write_1(sc, R92C_USTIME_TSF, 0x50);
	rtwn_write_1(sc, R92C_USTIME_EDCA, 0x50);
}