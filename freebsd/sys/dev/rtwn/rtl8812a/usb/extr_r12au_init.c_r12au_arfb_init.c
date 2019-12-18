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
 scalar_t__ R12A_ARFR_2G (int) ; 
 scalar_t__ R12A_ARFR_5G (int) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,scalar_t__,int) ; 

__attribute__((used)) static void
r12au_arfb_init(struct rtwn_softc *sc)
{
	/* ARFB table 9 for 11ac 5G 2SS. */
	rtwn_write_4(sc, R12A_ARFR_5G(0), 0x00000010);
	rtwn_write_4(sc, R12A_ARFR_5G(0) + 4, 0xfffff000);

	/* ARFB table 10 for 11ac 5G 1SS. */
	rtwn_write_4(sc, R12A_ARFR_5G(1), 0x00000010);
	rtwn_write_4(sc, R12A_ARFR_5G(1) + 4, 0x003ff000);

	/* ARFB table 11 for 11ac 2G 1SS. */
	rtwn_write_4(sc, R12A_ARFR_2G(0), 0x00000015);
	rtwn_write_4(sc, R12A_ARFR_2G(0) + 4, 0x003ff000);

	/* ARFB table 12 for 11ac 2G 2SS. */
	rtwn_write_4(sc, R12A_ARFR_2G(1), 0x00000015);
	rtwn_write_4(sc, R12A_ARFR_2G(1) + 4, 0xffcff000);
}