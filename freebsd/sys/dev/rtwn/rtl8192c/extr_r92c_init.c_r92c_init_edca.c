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
 int /*<<< orphan*/  R92C_EDCA_BE_PARAM ; 
 int /*<<< orphan*/  R92C_EDCA_BK_PARAM ; 
 int /*<<< orphan*/  R92C_EDCA_VI_PARAM ; 
 int /*<<< orphan*/  R92C_EDCA_VO_PARAM ; 
 int /*<<< orphan*/  R92C_MAC_SPEC_SIFS ; 
 int /*<<< orphan*/  R92C_SIFS_CCK ; 
 int /*<<< orphan*/  R92C_SIFS_OFDM ; 
 int /*<<< orphan*/  R92C_SPEC_SIFS ; 
 int /*<<< orphan*/  rtwn_write_2 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r92c_init_edca(struct rtwn_softc *sc)
{
	/* SIFS */
	rtwn_write_2(sc, R92C_SPEC_SIFS, 0x100a);
	rtwn_write_2(sc, R92C_MAC_SPEC_SIFS, 0x100a);
	rtwn_write_2(sc, R92C_SIFS_CCK, 0x100a);
	rtwn_write_2(sc, R92C_SIFS_OFDM, 0x100a);
	/* TXOP */
	rtwn_write_4(sc, R92C_EDCA_BE_PARAM, 0x005ea42b);
	rtwn_write_4(sc, R92C_EDCA_BK_PARAM, 0x0000a44f);
	rtwn_write_4(sc, R92C_EDCA_VI_PARAM, 0x005ea324);
	rtwn_write_4(sc, R92C_EDCA_VO_PARAM, 0x002fa226);
}