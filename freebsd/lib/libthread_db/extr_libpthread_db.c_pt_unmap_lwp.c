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
struct TYPE_5__ {unsigned int map_len; TYPE_1__* map; } ;
typedef  TYPE_2__ td_thragent_t ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ lwp; } ;

/* Variables and functions */
 scalar_t__ PT_LWP ; 
 scalar_t__ PT_NONE ; 

__attribute__((used)) static void
pt_unmap_lwp(const td_thragent_t *ta, lwpid_t lwp)
{
	unsigned int i;

	for (i = 0; i < ta->map_len; ++i) {
		if (ta->map[i].type == PT_LWP && ta->map[i].lwp == lwp) {
			ta->map[i].type = PT_NONE;
			return;
		}
	}
}