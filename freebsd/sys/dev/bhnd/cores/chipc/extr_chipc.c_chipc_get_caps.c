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
struct chipc_caps {int dummy; } ;
struct chipc_softc {struct chipc_caps caps; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct chipc_caps *
chipc_get_caps(device_t dev)
{
	struct chipc_softc	*sc;

	sc = device_get_softc(dev);
	return (&sc->caps);
}