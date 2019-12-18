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
typedef  int UWORD ;
typedef  size_t UBYTE ;
struct TYPE_2__ {size_t w; size_t h; size_t x; int data_idx; scalar_t__ y; } ;

/* Variables and functions */
 int /*<<< orphan*/ * data ; 
 TYPE_1__* icons ; 
 int /*<<< orphan*/ * selected_data ; 
 int /*<<< orphan*/  switch_data (size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void change_icon(UBYTE icon, UBYTE selected)
{
  UBYTE x, y;

  for(x = 0; x < icons[icon].w; x++)
    for(y = 0; y < icons[icon].h; y++)
      switch_data(icons[icon].x + x,
		  icons[icon].y + y,
		  (selected ?
		   selected_data[icons[icon].data_idx+((UWORD)x<<1)+y] :
		   data[icons[icon].data_idx+((UWORD)x<<1)+y]),
		  NULL);
}