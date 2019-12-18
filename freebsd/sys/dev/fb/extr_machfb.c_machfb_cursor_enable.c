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
struct machfb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_TEST_CNTL ; 
 int HWCURSOR_ENABLE ; 
 int regr (struct machfb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (struct machfb_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
machfb_cursor_enable(struct machfb_softc *sc, int onoff)
{

	if (onoff)
		regw(sc, GEN_TEST_CNTL,
		    regr(sc, GEN_TEST_CNTL) | HWCURSOR_ENABLE);
	else
		regw(sc, GEN_TEST_CNTL,
		    regr(sc, GEN_TEST_CNTL) &~ HWCURSOR_ENABLE);
}