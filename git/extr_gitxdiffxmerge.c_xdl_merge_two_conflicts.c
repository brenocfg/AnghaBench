#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; scalar_t__ i2; scalar_t__ chg2; scalar_t__ i1; scalar_t__ chg1; } ;
typedef  TYPE_1__ xdmerge_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void xdl_merge_two_conflicts(xdmerge_t *m)
{
	xdmerge_t *next_m = m->next;
	m->chg1 = next_m->i1 + next_m->chg1 - m->i1;
	m->chg2 = next_m->i2 + next_m->chg2 - m->i2;
	m->next = next_m->next;
	free(next_m);
}