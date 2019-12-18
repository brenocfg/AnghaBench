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
struct iwm_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct iwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int iwm_detach_local (struct iwm_softc*,int) ; 

__attribute__((used)) static int
iwm_detach(device_t dev)
{
	struct iwm_softc *sc = device_get_softc(dev);

	return (iwm_detach_local(sc, 1));
}