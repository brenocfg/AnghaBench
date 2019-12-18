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
struct bhnd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int bhnd_delete_children (struct bhnd_softc*) ; 
 struct bhnd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ ) ; 

int
bhnd_generic_detach(device_t dev)
{
	struct bhnd_softc	*sc;
	int			 error;

	if (!device_is_attached(dev))
		return (EBUSY);

	sc = device_get_softc(dev);

	if ((error = bhnd_delete_children(sc)))
		return (error);

	return (0);
}