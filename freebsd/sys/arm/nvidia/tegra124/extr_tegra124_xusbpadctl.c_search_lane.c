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
struct padctl_softc {int dummy; } ;
struct padctl_lane {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct padctl_lane* lanes_tbl ; 
 int nitems (struct padctl_lane*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct padctl_lane *
search_lane(struct padctl_softc *sc, char *lane_name)
{
	int i;

	for (i = 0; i < nitems(lanes_tbl); i++) {
		if (strcmp(lane_name, lanes_tbl[i].name) == 0)
			return 	(lanes_tbl + i);
	}
	return (NULL);
}