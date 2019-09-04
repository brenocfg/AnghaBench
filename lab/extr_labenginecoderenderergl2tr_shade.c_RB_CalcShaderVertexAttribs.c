#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* shader; } ;
typedef  TYPE_2__ shaderCommands_t ;
struct TYPE_7__ {scalar_t__ vertexAnimation; } ;
struct TYPE_5__ {unsigned int vertexAttribs; } ;

/* Variables and functions */
 unsigned int ATTR_NORMAL ; 
 unsigned int ATTR_NORMAL2 ; 
 unsigned int ATTR_POSITION2 ; 
 unsigned int ATTR_TANGENT2 ; 
 TYPE_3__ glState ; 

__attribute__((used)) static unsigned int RB_CalcShaderVertexAttribs( shaderCommands_t *input )
{
	unsigned int vertexAttribs = input->shader->vertexAttribs;

	if(glState.vertexAnimation)
	{
		vertexAttribs |= ATTR_POSITION2;
		if (vertexAttribs & ATTR_NORMAL)
		{
			vertexAttribs |= ATTR_NORMAL2;
			vertexAttribs |= ATTR_TANGENT2;
		}
	}

	return vertexAttribs;
}