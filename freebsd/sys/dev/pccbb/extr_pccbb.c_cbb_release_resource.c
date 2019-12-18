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
struct resource {int dummy; } ;
struct cbb_softc {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CBB_16BIT_CARD ; 
 int cbb_cardbus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int cbb_pcic_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
cbb_release_resource(device_t brdev, device_t child, int type, int rid,
    struct resource *r)
{
	struct cbb_softc *sc = device_get_softc(brdev);

	if (sc->flags & CBB_16BIT_CARD)
		return (cbb_pcic_release_resource(brdev, child, type,
		    rid, r));
	else
		return (cbb_cardbus_release_resource(brdev, child, type,
		    rid, r));
}