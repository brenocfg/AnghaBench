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
struct TYPE_4__ {struct TYPE_4__* l_prev; struct TYPE_4__* l_next; scalar_t__ areanum; } ;
typedef  TYPE_1__ tmp_area_t ;
struct TYPE_5__ {int /*<<< orphan*/  numareas; TYPE_1__* areas; int /*<<< orphan*/  areanum; } ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 TYPE_2__ tmpaasworld ; 

tmp_area_t *AAS_AllocTmpArea(void)
{
	tmp_area_t *tmparea;

	tmparea = (tmp_area_t *) GetClearedMemory(sizeof(tmp_area_t));
	tmparea->areanum = tmpaasworld.areanum++;
	tmparea->l_prev = NULL;
	tmparea->l_next = tmpaasworld.areas;
	if (tmpaasworld.areas) tmpaasworld.areas->l_prev = tmparea;
	tmpaasworld.areas = tmparea;
	tmpaasworld.numareas++;
	return tmparea;
}