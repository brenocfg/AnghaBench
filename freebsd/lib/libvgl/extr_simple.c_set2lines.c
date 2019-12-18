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

__attribute__((used)) static inline void
set2lines(VGLBitmap *object, int x, int y, int xc, int yc, u_long color)
{
  if (x!=0) { 
    VGLLine(object, xc+x, yc+y, xc-x, yc+y, color); 
    if (y!=0) 
      VGLLine(object, xc+x, yc-y, xc-x, yc-y, color); 
  } 
  else { 
    VGLLine(object, xc, yc+y, xc, yc-y, color); 
  } 
}