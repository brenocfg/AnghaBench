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
struct sort_mods {scalar_t__ fflag; scalar_t__ dflag; scalar_t__ hflag; scalar_t__ Rflag; scalar_t__ rflag; scalar_t__ gflag; scalar_t__ nflag; scalar_t__ Vflag; scalar_t__ Mflag; } ;

/* Variables and functions */

__attribute__((used)) static bool
sort_modifier_empty(struct sort_mods *sm)
{

	if (sm == NULL)
		return (true);
	return (!(sm->Mflag || sm->Vflag || sm->nflag || sm->gflag ||
	    sm->rflag || sm->Rflag || sm->hflag || sm->dflag || sm->fflag));
}