#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {TYPE_2__* sc; } ;
typedef  TYPE_1__ scr_stat ;
struct TYPE_5__ {int /*<<< orphan*/  font_loading_in_progress; int /*<<< orphan*/  adp; } ;
typedef  TYPE_2__ sc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  vidd_load_font (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int) ; 

void
sc_load_font(scr_stat *scp, int page, int size, int width, u_char *buf,
	     int base, int count)
{
    sc_softc_t *sc;

    sc = scp->sc;
    sc->font_loading_in_progress = TRUE;
    vidd_load_font(sc->adp, page, size, width, buf, base, count);
    sc->font_loading_in_progress = FALSE;
}