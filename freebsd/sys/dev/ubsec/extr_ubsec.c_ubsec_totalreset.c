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
struct ubsec_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubsec_cleanchip (struct ubsec_softc*) ; 
 int /*<<< orphan*/  ubsec_init_board (struct ubsec_softc*) ; 
 int /*<<< orphan*/  ubsec_reset_board (struct ubsec_softc*) ; 

__attribute__((used)) static void
ubsec_totalreset(struct ubsec_softc *sc)
{
	ubsec_reset_board(sc);
	ubsec_init_board(sc);
	ubsec_cleanchip(sc);
}