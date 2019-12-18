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
typedef  int /*<<< orphan*/  video_adapter_t ;
struct machfb_softc {int /*<<< orphan*/  sc_height; int /*<<< orphan*/  sc_width; } ;

/* Variables and functions */
 int SC_NORM_ATTR ; 
 int /*<<< orphan*/  machfb_fill_rect (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
machfb_clear(video_adapter_t *adp)
{
	struct machfb_softc *sc;

	sc = (struct machfb_softc *)adp;

	machfb_fill_rect(adp, (SC_NORM_ATTR >> 4) & 0xf, 0, 0, sc->sc_width,
	    sc->sc_height);

	return (0);
}