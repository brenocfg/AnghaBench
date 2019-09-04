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
typedef  int /*<<< orphan*/  glIndex_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_OFFSET (int) ; 
 int /*<<< orphan*/  GL_INDEX_TYPE ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  qglDrawElements (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void R_DrawElements( int numIndexes, int firstIndex )
{
	qglDrawElements(GL_TRIANGLES, numIndexes, GL_INDEX_TYPE, BUFFER_OFFSET(firstIndex * sizeof(glIndex_t)));
}