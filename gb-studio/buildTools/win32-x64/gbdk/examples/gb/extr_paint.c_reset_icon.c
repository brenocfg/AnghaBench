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
typedef  size_t UBYTE ;
struct TYPE_2__ {size_t w; size_t h; size_t data_idx; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/ * data_buffer ; 
 TYPE_1__* icons ; 
 int /*<<< orphan*/  switch_data (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void reset_icon(UBYTE icon)
{
  UBYTE x, y;

  for(x = 0; x < icons[icon].w; x++)
    for(y = 0; y < icons[icon].h; y++)
      switch_data(icons[icon].x + x,
		  icons[icon].y + y,
		  data_buffer[icons[icon].data_idx+(x<<1)+y],
		  NULL);
}