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
struct sbc_softc {int /*<<< orphan*/  child_pcm; int /*<<< orphan*/  child_midi1; int /*<<< orphan*/  child_midi2; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sbc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (struct sbc_softc*) ; 
 int /*<<< orphan*/  sbc_lock (struct sbc_softc*) ; 
 int /*<<< orphan*/  sbc_lockdestroy (struct sbc_softc*) ; 

__attribute__((used)) static int
sbc_detach(device_t dev)
{
	struct sbc_softc *scp = device_get_softc(dev);

	sbc_lock(scp);
	device_delete_child(dev, scp->child_midi2);
	device_delete_child(dev, scp->child_midi1);
	device_delete_child(dev, scp->child_pcm);
	release_resource(scp);
	sbc_lockdestroy(scp);
	return bus_generic_detach(dev);
}