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
struct video_adapter_softc {int initialized; int /*<<< orphan*/  va; int /*<<< orphan*/  depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_DEPTH ; 
 int /*<<< orphan*/  FB_HEIGHT ; 
 int /*<<< orphan*/  FB_WIDTH ; 
 struct video_adapter_softc va_softc ; 
 int /*<<< orphan*/  versatilefb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
versatilefb_configure(int flags)
{
	struct video_adapter_softc *va_sc;

	va_sc = &va_softc;

	if (va_sc->initialized)
		return (0);

	va_sc->width = FB_WIDTH;
	va_sc->height = FB_HEIGHT;
	va_sc->depth = FB_DEPTH;

	versatilefb_init(0, &va_sc->va, 0);

	va_sc->initialized = 1;

	return (0);
}