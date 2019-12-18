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
struct TYPE_4__ {int /*<<< orphan*/ * next_area; int /*<<< orphan*/ * prev_area; struct TYPE_4__* next_ent; struct TYPE_4__* prev_ent; } ;
typedef  TYPE_1__ aas_link_t ;
struct TYPE_5__ {TYPE_1__* freelinks; } ;

/* Variables and functions */
 TYPE_2__ aasworld ; 
 int /*<<< orphan*/  numaaslinks ; 

void AAS_DeAllocAASLink(aas_link_t *link)
{
	if (aasworld.freelinks) aasworld.freelinks->prev_ent = link;
	link->prev_ent = NULL;
	link->next_ent = aasworld.freelinks;
	link->prev_area = NULL;
	link->next_area = NULL;
	aasworld.freelinks = link;
	numaaslinks++;
}