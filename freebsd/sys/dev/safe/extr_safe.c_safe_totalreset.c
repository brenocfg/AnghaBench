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
struct safe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  safe_cleanchip (struct safe_softc*) ; 
 int /*<<< orphan*/  safe_init_board (struct safe_softc*) ; 
 int /*<<< orphan*/  safe_reset_board (struct safe_softc*) ; 

__attribute__((used)) static void
safe_totalreset(struct safe_softc *sc)
{
	safe_reset_board(sc);
	safe_init_board(sc);
	safe_cleanchip(sc);
}