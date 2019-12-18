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
struct ukswitch_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UKSWITCH_LOCK_ASSERT (struct ukswitch_softc*,int /*<<< orphan*/ ) ; 
 struct ukswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ukswitch_readreg(device_t dev, int addr)
{
	struct ukswitch_softc *sc;

	sc = device_get_softc(dev);
	UKSWITCH_LOCK_ASSERT(sc, MA_OWNED);

	/* Not supported. */
	return (0);
}