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
struct siba_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIBA_LOCK_DESTROY (struct siba_softc*) ; 
 int bhnd_generic_detach (int /*<<< orphan*/ ) ; 
 struct siba_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
siba_detach(device_t dev)
{
	struct siba_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	if ((error = bhnd_generic_detach(dev)))
		return (error);

	SIBA_LOCK_DESTROY(sc);

	return (0);
}