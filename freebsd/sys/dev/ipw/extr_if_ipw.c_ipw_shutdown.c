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
struct ipw_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ipw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_stop (struct ipw_softc*) ; 

__attribute__((used)) static int
ipw_shutdown(device_t dev)
{
	struct ipw_softc *sc = device_get_softc(dev);

	ipw_stop(sc);

	return 0;
}