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
struct gdstate {TYPE_1__* tokenp; void* DSTmode; int /*<<< orphan*/  Timezone; int /*<<< orphan*/  HaveZone; } ;
struct TYPE_2__ {scalar_t__ token; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 void* DSToff ; 
 void* DSTon ; 
 scalar_t__ tDAYZONE ; 
 scalar_t__ tDST ; 
 scalar_t__ tZONE ; 

__attribute__((used)) static int
zonephrase(struct gdstate *gds)
{
	if (gds->tokenp[0].token == tZONE
	    && gds->tokenp[1].token == tDST) {
		gds->HaveZone++;
		gds->Timezone = gds->tokenp[0].value;
		gds->DSTmode = DSTon;
		gds->tokenp += 1;
		return 1;
	}

	if (gds->tokenp[0].token == tZONE) {
		gds->HaveZone++;
		gds->Timezone = gds->tokenp[0].value;
		gds->DSTmode = DSToff;
		gds->tokenp += 1;
		return 1;
	}

	if (gds->tokenp[0].token == tDAYZONE) {
		gds->HaveZone++;
		gds->Timezone = gds->tokenp[0].value;
		gds->DSTmode = DSTon;
		gds->tokenp += 1;
		return 1;
	}
	return 0;
}