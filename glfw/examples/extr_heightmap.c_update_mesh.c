#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int MAP_NUM_TOTAL_VERTICES ; 
 int /*<<< orphan*/  glBufferSubData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** map_vertices ; 

__attribute__((used)) static void update_mesh(void)
{
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[1][0]);
}