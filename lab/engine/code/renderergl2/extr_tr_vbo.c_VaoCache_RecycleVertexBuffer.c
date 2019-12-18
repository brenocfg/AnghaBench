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
struct TYPE_4__ {scalar_t__ vertexOffset; TYPE_1__* vao; } ;
struct TYPE_3__ {int /*<<< orphan*/  vertexesSize; int /*<<< orphan*/  vertexesVBO; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_DYNAMIC_DRAW ; 
 int /*<<< orphan*/  qglBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBufferData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__ vc ; 

void VaoCache_RecycleVertexBuffer(void)
{
	qglBindBuffer(GL_ARRAY_BUFFER, vc.vao->vertexesVBO);
	qglBufferData(GL_ARRAY_BUFFER, vc.vao->vertexesSize, NULL, GL_DYNAMIC_DRAW);
	vc.vertexOffset = 0;
}