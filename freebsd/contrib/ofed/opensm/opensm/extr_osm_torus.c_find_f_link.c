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
struct link {TYPE_1__* end; } ;
struct fabric {unsigned int link_cnt; struct link** link; } ;
typedef  scalar_t__ guid_t ;
struct TYPE_2__ {scalar_t__ n_id; int port; } ;

/* Variables and functions */

__attribute__((used)) static
struct link *find_f_link(struct fabric *f,
			 guid_t guid0, int port0, guid_t guid1, int port1)
{
	unsigned l;
	struct link *link;

	if (f->link) {
		for (l = 0; l < f->link_cnt; l++) {
			link = f->link[l];
			if ((link->end[0].n_id == guid0 &&
			     link->end[0].port == port0 &&
			     link->end[1].n_id == guid1 &&
			     link->end[1].port == port1) ||
			    (link->end[0].n_id == guid1 &&
			     link->end[0].port == port1 &&
			     link->end[1].n_id == guid0 &&
			     link->end[1].port == port0))
				return link;
		}
	}
	return NULL;
}