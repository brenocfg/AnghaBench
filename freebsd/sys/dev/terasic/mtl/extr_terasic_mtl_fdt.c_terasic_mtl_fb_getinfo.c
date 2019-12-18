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
struct fb_info {int dummy; } ;
struct terasic_mtl_softc {struct fb_info mtl_fb_info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct terasic_mtl_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fb_info *
terasic_mtl_fb_getinfo(device_t dev)
{
        struct terasic_mtl_softc *sc;

        sc = device_get_softc(dev);
        return (&sc->mtl_fb_info);
}