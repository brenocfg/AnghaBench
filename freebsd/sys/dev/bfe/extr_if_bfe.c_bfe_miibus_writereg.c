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
struct bfe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfe_writephy (struct bfe_softc*,int,int) ; 
 struct bfe_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bfe_miibus_writereg(device_t dev, int phy, int reg, int val)
{
	struct bfe_softc *sc;

	sc = device_get_softc(dev);
	bfe_writephy(sc, reg, val);

	return (0);
}