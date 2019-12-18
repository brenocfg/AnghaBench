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
struct cdceem_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDCEEM_DEBUG (struct cdceem_softc*,char*) ; 
 struct cdceem_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdceem_resume(device_t dev)
{
	struct cdceem_softc *sc = device_get_softc(dev);

	CDCEEM_DEBUG(sc, "go");
	return (0);
}