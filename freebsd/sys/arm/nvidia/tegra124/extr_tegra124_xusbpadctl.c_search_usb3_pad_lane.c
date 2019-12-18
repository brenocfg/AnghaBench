#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct padctl_softc {int /*<<< orphan*/  dev; } ;
struct padctl_lane {size_t mux_idx; int /*<<< orphan*/  name; int /*<<< orphan*/ * mux; } ;
struct TYPE_3__ {int port_idx; int /*<<< orphan*/  lane_idx; int /*<<< orphan*/  pad_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* lane_map_tbl ; 
 int nitems (TYPE_1__*) ; 
 struct padctl_lane* search_pad_lane (struct padctl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct padctl_lane *
search_usb3_pad_lane(struct padctl_softc *sc, int idx)
{
	int i;
	struct padctl_lane *lane, *tmp;

	lane = NULL;
	for (i = 0; i < nitems(lane_map_tbl); i++) {
		if (idx != lane_map_tbl[i].port_idx)
			continue;
		tmp = search_pad_lane(sc, lane_map_tbl[i].pad_type,
		    lane_map_tbl[i].lane_idx);
		if (tmp == NULL)
			continue;
		if (strcmp(tmp->mux[tmp->mux_idx], "usb3-ss") != 0)
			continue;
		if (lane != NULL) {
			device_printf(sc->dev, "Duplicated mappings found for"
			 " lanes: %s and %s\n", lane->name, tmp->name);
			return (NULL);
		}
		lane = tmp;
	}
	return (lane);
}