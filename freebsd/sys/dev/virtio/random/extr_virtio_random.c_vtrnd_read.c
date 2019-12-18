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

/* Variables and functions */
 struct vtrnd_softc* g_vtrnd_softc ; 
 int vtrnd_harvest (struct vtrnd_softc*,void*,size_t*) ; 

__attribute__((used)) static unsigned
vtrnd_read(void *buf, unsigned usz)
{
	struct vtrnd_softc *sc;
	size_t sz;
	int error;

	sc = g_vtrnd_softc;
	if (sc == NULL)
		return (0);

	sz = usz;
	error = vtrnd_harvest(sc, buf, &sz);
	if (error != 0)
		return (0);

	return (sz);
}