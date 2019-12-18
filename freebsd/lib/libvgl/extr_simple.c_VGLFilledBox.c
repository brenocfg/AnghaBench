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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  VGLBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  VGLLine (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 

void
VGLFilledBox(VGLBitmap *object, int x1, int y1, int x2, int y2, u_long color)
{
  int y;

  for (y=y1; y<=y2; y++) VGLLine(object, x1, y, x2, y, color);
}