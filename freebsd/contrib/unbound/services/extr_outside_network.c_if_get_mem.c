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
struct port_if {int avail_total; int maxout; int inuse; TYPE_1__** out; } ;
struct port_comm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cp; } ;

/* Variables and functions */
 scalar_t__ comm_point_get_mem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
if_get_mem(struct port_if* pif)
{
	size_t s;
	int i;
	s = sizeof(*pif) + sizeof(int)*pif->avail_total +
		sizeof(struct port_comm*)*pif->maxout;
	for(i=0; i<pif->inuse; i++)
		s += sizeof(*pif->out[i]) + 
			comm_point_get_mem(pif->out[i]->cp);
	return s;
}