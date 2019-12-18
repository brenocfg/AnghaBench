#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ enum_addr; } ;
struct bhndb_softc {TYPE_1__ chipid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned long long) ; 

__attribute__((used)) static int
bhndb_child_location_str(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	struct bhndb_softc *sc;

	sc = device_get_softc(dev);

	snprintf(buf, buflen, "base=0x%llx",
	    (unsigned long long) sc->chipid.enum_addr);
	return (0);
}