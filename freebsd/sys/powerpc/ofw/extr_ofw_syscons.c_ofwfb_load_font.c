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
typedef  int /*<<< orphan*/  u_char ;
struct ofwfb_softc {int /*<<< orphan*/ * sc_font; } ;

/* Variables and functions */

__attribute__((used)) static int
ofwfb_load_font(video_adapter_t *adp, int page, int size, int width,
    u_char *data, int c, int count)
{
	struct ofwfb_softc *sc;

	sc = (struct ofwfb_softc *)adp;

	/*
	 * syscons code has already determined that current width/height
	 * are unchanged for this new font
	 */
	sc->sc_font = data;
	return (0);
}