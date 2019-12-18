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
struct iwn_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iwn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwn_stop (struct iwn_softc*) ; 

__attribute__((used)) static int
iwn_shutdown(device_t dev)
{
	struct iwn_softc *sc = device_get_softc(dev);

	iwn_stop(sc);
	return 0;
}