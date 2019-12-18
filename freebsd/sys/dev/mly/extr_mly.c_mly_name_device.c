#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mly_softc {TYPE_1__** mly_btl; } ;
struct cam_periph {char* periph_name; int /*<<< orphan*/  unit_number; } ;
struct TYPE_2__ {scalar_t__* mb_name; } ;

/* Variables and functions */
 int ENOENT ; 
 struct cam_periph* mly_find_periph (struct mly_softc*,int,int) ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mly_name_device(struct mly_softc *sc, int bus, int target)
{
    struct cam_periph	*periph;

    if ((periph = mly_find_periph(sc, bus, target)) != NULL) {
	sprintf(sc->mly_btl[bus][target].mb_name, "%s%d", periph->periph_name, periph->unit_number);
	return(0);
    }
    sc->mly_btl[bus][target].mb_name[0] = 0;
    return(ENOENT);
}