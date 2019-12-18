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
struct ptnet_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ptnet_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptnet_device_shutdown (struct ptnet_softc*) ; 

__attribute__((used)) static int
ptnet_shutdown(device_t dev)
{
	struct ptnet_softc *sc = device_get_softc(dev);

	ptnet_device_shutdown(sc);

	return (0);
}