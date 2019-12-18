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
struct ofwfb_softc {int (* sc_blank ) (int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ofwfb_blank_display(video_adapter_t *adp, int mode)
{
	struct ofwfb_softc *sc;

	sc = (struct ofwfb_softc *)adp;

	return ((*sc->sc_blank)(adp, mode));
}