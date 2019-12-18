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
struct padctl_softc {int dummy; } ;
struct padctl_lane {int idx; TYPE_1__* pad; int /*<<< orphan*/  enabled; } ;
typedef  enum padctl_pad_type { ____Placeholder_padctl_pad_type } padctl_pad_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 struct padctl_lane* lanes_tbl ; 
 int nitems (struct padctl_lane*) ; 

__attribute__((used)) static struct padctl_lane *
search_pad_lane(struct padctl_softc *sc, enum padctl_pad_type type, int idx)
{
	int i;

	for (i = 0; i < nitems(lanes_tbl); i++) {
		if (!lanes_tbl[i].enabled)
			continue;
		if (type == lanes_tbl[i].pad->type && idx == lanes_tbl[i].idx)
			return 	(lanes_tbl + i);
	}
	return (NULL);
}