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
struct video_adapter_softc {int initialized; int width; int height; int bpp; int stride; int /*<<< orphan*/  va; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu3fb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct video_adapter_softc va_softc ; 

__attribute__((used)) static int
ipu3fb_configure(int flags)
{
	struct video_adapter_softc *sc;

	sc = &va_softc;

	if (sc->initialized)
		return 0;

	sc->width = 640;
	sc->height = 480;
	sc->bpp = 2;
	sc->stride = sc->width * sc->bpp;

	ipu3fb_init(0, &sc->va, 0);

	sc->initialized = 1;

	return (0);
}