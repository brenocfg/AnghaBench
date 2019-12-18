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
struct videomode {int dummy; } ;
struct tda19988_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct tda19988_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda19988_init_encoder (struct tda19988_softc*,struct videomode const*) ; 

__attribute__((used)) static int
tda19988_set_videomode(device_t dev, const struct videomode *mode)
{
	struct tda19988_softc *sc;

	sc = device_get_softc(dev);

	tda19988_init_encoder(sc, mode);

	return (0);
}