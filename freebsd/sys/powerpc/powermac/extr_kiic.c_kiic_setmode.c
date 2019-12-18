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
typedef  int u_int ;
struct kiic_softc {int dummy; } ;

/* Variables and functions */
 int I2C_MODE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MODE ; 
 int kiic_readreg (struct kiic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kiic_writereg (struct kiic_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
kiic_setmode(struct kiic_softc *sc, u_int mode)
{
	u_int x;

	KASSERT((mode & ~I2C_MODE) == 0, ("bad mode"));
	x = kiic_readreg(sc, MODE);
	x &= ~I2C_MODE;
	x |= mode;
	kiic_writereg(sc, MODE, x);
}