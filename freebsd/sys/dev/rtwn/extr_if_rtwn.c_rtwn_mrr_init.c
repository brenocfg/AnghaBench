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
 scalar_t__ R92C_DARFRC ; 
 int R92C_DARFRC_SIZE ; 
 scalar_t__ R92C_RARFRC ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,scalar_t__,int) ; 

__attribute__((used)) static void
rtwn_mrr_init(struct rtwn_softc *sc)
{
	int i;

	/* Drop rate index by 1 per retry. */
	for (i = 0; i < R92C_DARFRC_SIZE; i++) {
		rtwn_write_1(sc, R92C_DARFRC + i, i + 1);
		rtwn_write_1(sc, R92C_RARFRC + i, i + 1);
	}
}