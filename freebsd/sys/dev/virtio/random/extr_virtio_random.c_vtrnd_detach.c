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
struct vtrnd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_HARDCLOCK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct vtrnd_softc* atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vtrnd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_vtrnd_softc ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int /*<<< orphan*/  memory_order_release ; 
 int /*<<< orphan*/  mstosbt (int) ; 
 int /*<<< orphan*/  random_source_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_vtrnd ; 
 int /*<<< orphan*/  tsleep_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtrnd_detach(device_t dev)
{
	struct vtrnd_softc *sc;

	sc = device_get_softc(dev);
	KASSERT(
	    atomic_load_explicit(&g_vtrnd_softc, memory_order_acquire) == sc,
	    ("only one global instance at a time"));

	random_source_deregister(&random_vtrnd);
	atomic_store_explicit(&g_vtrnd_softc, NULL, memory_order_release);

	/*
	 * Unfortunately, deregister does not guarantee our source callback
	 * will not be invoked after it returns.  Use a kludge to prevent some,
	 * but not all, possible races.
	 */
	tsleep_sbt(&g_vtrnd_softc, 0, "vtrnddet", mstosbt(50), 0, C_HARDCLOCK);

	return (0);
}