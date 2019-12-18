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
typedef  int UBYTE ;
struct TYPE_2__ {scalar_t__ x; scalar_t__ y; } ;

/* Variables and functions */
 scalar_t__ SCX_REG ; 
 scalar_t__ SCY_REG ; 
 TYPE_1__ camera_dest ; 

UBYTE SceneCameraAtDest_b()
{
  return SCX_REG == camera_dest.x && SCY_REG == camera_dest.y;
}