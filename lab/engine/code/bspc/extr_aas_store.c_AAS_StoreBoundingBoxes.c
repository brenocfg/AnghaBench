#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  aas_bbox_t ;
struct TYPE_6__ {int numbboxes; int /*<<< orphan*/  bboxes; } ;
struct TYPE_5__ {int numbboxes; int /*<<< orphan*/  bboxes; } ;
struct TYPE_4__ {int max_bboxes; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int) ; 
 TYPE_3__ aasworld ; 
 TYPE_2__ cfg ; 
 TYPE_1__ max_aas ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void AAS_StoreBoundingBoxes(void)
{
	if (cfg.numbboxes > max_aas.max_bboxes)
	{
		Error("more than %d bounding boxes", max_aas.max_bboxes);
	} //end if
	aasworld.numbboxes = cfg.numbboxes;
	memcpy(aasworld.bboxes, cfg.bboxes, cfg.numbboxes * sizeof(aas_bbox_t));
}