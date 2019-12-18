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
typedef  int /*<<< orphan*/  mat4_t ;
struct TYPE_2__ {int /*<<< orphan*/  modelviewProjection; int /*<<< orphan*/  modelview; int /*<<< orphan*/  projection; } ;

/* Variables and functions */
 int /*<<< orphan*/  Mat4Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Mat4Multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ glState ; 

void GL_SetModelviewMatrix(mat4_t matrix)
{
	Mat4Copy(matrix, glState.modelview);
	Mat4Multiply(glState.projection, glState.modelview, glState.modelviewProjection);	
}