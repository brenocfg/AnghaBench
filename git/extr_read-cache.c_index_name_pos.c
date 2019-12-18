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
struct index_state {int dummy; } ;

/* Variables and functions */
 int index_name_stage_pos (struct index_state const*,char const*,int,int /*<<< orphan*/ ) ; 

int index_name_pos(const struct index_state *istate, const char *name, int namelen)
{
	return index_name_stage_pos(istate, name, namelen, 0);
}