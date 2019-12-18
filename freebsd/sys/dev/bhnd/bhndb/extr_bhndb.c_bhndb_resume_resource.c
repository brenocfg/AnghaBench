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
struct bhndb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BHNDB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIO ; 
 int RF_ACTIVE ; 
 int SYS_RES_MEMORY ; 
 int bhndb_try_activate_resource (struct bhndb_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ *) ; 
 struct bhndb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_device (struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int /*<<< orphan*/  rman_get_rid (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 

__attribute__((used)) static int
bhndb_resume_resource(device_t dev, device_t child, int type,
    struct resource *r)
{
	struct bhndb_softc	*sc;

	sc = device_get_softc(dev);

	/* Non-MMIO resources (e.g. IRQs) are handled solely by our parent */
	if (type != SYS_RES_MEMORY)
		return (0);

	/* Inactive resources don't require reallocation of bridge resources */
	if (!(rman_get_flags(r) & RF_ACTIVE))
		return (0);

	if (BHNDB_DEBUG(PRIO))
		device_printf(child, "resume resource type=%d 0x%jx+0x%jx\n",
		    type, rman_get_start(r), rman_get_size(r));

	return (bhndb_try_activate_resource(sc, rman_get_device(r), type,
	    rman_get_rid(r), r, NULL));
}