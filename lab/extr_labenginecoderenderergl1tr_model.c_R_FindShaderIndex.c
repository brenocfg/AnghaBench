#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int index; scalar_t__ defaultShader; } ;
typedef  TYPE_1__ shader_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIGHTMAP_NONE ; 
 TYPE_1__* R_FindShader (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 

int R_FindShaderIndex(const char *shader_name)
{
	shader_t *sh = R_FindShader( shader_name, LIGHTMAP_NONE, qtrue );
	return sh->defaultShader ? 0 : sh->index;
}