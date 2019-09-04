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
typedef  int /*<<< orphan*/  vao_t ;
struct TYPE_4__ {int /*<<< orphan*/ * currentVao; } ;
struct TYPE_3__ {int /*<<< orphan*/  useInternalVao; int /*<<< orphan*/ * vao; int /*<<< orphan*/  cubemapIndex; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_BeginSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  R_BindVao (int /*<<< orphan*/ *) ; 
 TYPE_2__ glState ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_1__ tess ; 

void RB_CheckVao(vao_t *vao)
{
	if (vao != glState.currentVao)
	{
		RB_EndSurface();
		RB_BeginSurface(tess.shader, tess.fogNum, tess.cubemapIndex);

		R_BindVao(vao);
	}

	if (vao != tess.vao)
		tess.useInternalVao = qfalse;
}