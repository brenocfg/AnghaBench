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
typedef  scalar_t__ uint32_t ;
struct ipu3sc_softc {scalar_t__ vbase; int /*<<< orphan*/  pbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ contigmalloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (scalar_t__) ; 

__attribute__((used)) static int
ipu3_fb_malloc(struct ipu3sc_softc *sc, size_t size)
{

	sc->vbase = (uint32_t)contigmalloc(size, M_DEVBUF, M_ZERO, 0, ~0,
	    PAGE_SIZE, 0);
	sc->pbase = vtophys(sc->vbase);

	return (0);
}