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
struct amdsmn_softc {int /*<<< orphan*/  smn_lock; int /*<<< orphan*/  smn_pciid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  amdsmn_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct amdsmn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amdsmn_attach(device_t dev)
{
	struct amdsmn_softc *sc = device_get_softc(dev);

	if (!amdsmn_match(device_get_parent(dev), &sc->smn_pciid))
		return (ENXIO);

	mtx_init(&sc->smn_lock, "SMN mtx", "SMN", MTX_DEF);
	return (0);
}