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
struct udl_softc {struct fb_info sc_fb_info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct udl_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fb_info *
udl_fb_getinfo(device_t dev)
{
	struct udl_softc *sc = device_get_softc(dev);

	return (&sc->sc_fb_info);
}