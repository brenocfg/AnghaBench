#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ numBatches; scalar_t__ numSurfaces; scalar_t__ indexOffset; TYPE_1__* vao; } ;
struct TYPE_3__ {int /*<<< orphan*/  indexesSize; int /*<<< orphan*/  indexesIBO; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DYNAMIC_DRAW ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  qglBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBufferData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ vc ; 

void VaoCache_RecycleIndexBuffer(void)
{
	qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vc.vao->indexesIBO);
	qglBufferData(GL_ELEMENT_ARRAY_BUFFER, vc.vao->indexesSize, NULL, GL_DYNAMIC_DRAW);
	vc.indexOffset = 0;
	vc.numSurfaces = 0;
	vc.numBatches = 0;
}