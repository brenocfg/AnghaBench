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
 scalar_t__ NBSFRAMES ; 
 scalar_t__ sframe ; 
 int /*<<< orphan*/  tile_sprite () ; 
 int time ; 

void animate_sprite()
{
  if((time&0x07) == 0) {
    sframe++;
    if(sframe == NBSFRAMES)
      sframe = 0;
    tile_sprite();
  }
}