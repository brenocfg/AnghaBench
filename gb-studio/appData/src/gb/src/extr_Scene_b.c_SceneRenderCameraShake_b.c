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

/* Variables and functions */
 int SCX_REG ; 
 int shake_time ; 

void SceneRenderCameraShake_b()
{
  // Handle Shake
  if (shake_time != 0)
  {
    SCX_REG += shake_time & 0x5;
  }
}