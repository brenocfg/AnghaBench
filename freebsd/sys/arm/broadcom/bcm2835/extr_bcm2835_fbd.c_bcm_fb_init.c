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
struct bcmsc_softc {int /*<<< orphan*/  dev; } ;
struct bcm2835_fb_config {scalar_t__ bpp; scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  yres; int /*<<< orphan*/  vyres; int /*<<< orphan*/  xres; int /*<<< orphan*/  vxres; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ FB_DEPTH ; 
 scalar_t__ bcm2835_mbox_fb_get_bpp (struct bcm2835_fb_config*) ; 
 scalar_t__ bcm2835_mbox_fb_get_w_h (struct bcm2835_fb_config*) ; 
 int bcm2835_mbox_fb_init (struct bcm2835_fb_config*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memset (struct bcm2835_fb_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bcm_fb_init(struct bcmsc_softc *sc, struct bcm2835_fb_config *fb)
{
	int err;

	err = 0;

	memset(fb, 0, sizeof(*fb));
	if (bcm2835_mbox_fb_get_w_h(fb) != 0)
		return (ENXIO);
	if (bcm2835_mbox_fb_get_bpp(fb) != 0)
		return (ENXIO);
	if (fb->bpp < FB_DEPTH) {
		device_printf(sc->dev, "changing fb bpp from %d to %d\n", fb->bpp, FB_DEPTH);
		fb->bpp = FB_DEPTH;
	} else
		device_printf(sc->dev, "keeping existing fb bpp of %d\n", fb->bpp);

	fb->vxres = fb->xres;
	fb->vyres = fb->yres;
	fb->xoffset = fb->yoffset = 0;

	if ((err = bcm2835_mbox_fb_init(fb)) != 0) {
		device_printf(sc->dev, "bcm2835_mbox_fb_init failed, err=%d\n", err);
		return (ENXIO);
	}

	return (0);
}