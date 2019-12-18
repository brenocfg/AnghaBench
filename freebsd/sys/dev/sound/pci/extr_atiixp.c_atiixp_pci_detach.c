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
struct atiixp_info {scalar_t__ st; scalar_t__ sh; int /*<<< orphan*/ * codec; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  atiixp_disable_interrupts (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_release_resource (struct atiixp_info*) ; 
 struct atiixp_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atiixp_pci_detach(device_t dev)
{
	int r;
	struct atiixp_info *sc;

	sc = pcm_getdevinfo(dev);
	if (sc != NULL) {
		if (sc->codec != NULL) {
			r = pcm_unregister(dev);
			if (r)
				return (r);
		}
		sc->codec = NULL;
		if (sc->st != 0 && sc->sh != 0)
			atiixp_disable_interrupts(sc);
		atiixp_release_resource(sc);
	}
	return (0);
}