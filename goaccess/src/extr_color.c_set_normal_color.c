#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int idx; int bg; int /*<<< orphan*/  fg; int /*<<< orphan*/  item; struct TYPE_6__* pair; } ;
typedef  TYPE_1__ GColors ;
typedef  TYPE_1__ GColorPair ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_NORMAL ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 void* color_list ; 
 int /*<<< orphan*/  init_pair (int,int /*<<< orphan*/ ,int) ; 
 void* list_create (TYPE_1__*) ; 
 TYPE_1__* new_gcolorpair () ; 
 TYPE_1__* new_gcolors () ; 
 void* pair_list ; 

void
set_normal_color (void)
{
  GColorPair *pair = new_gcolorpair ();
  GColors *color = new_gcolors ();

  pair->idx = 1;
  pair->fg = COLOR_WHITE;
  pair->bg = -1;

  color->pair = pair;
  color->item = COLOR_NORMAL;

  pair_list = list_create (pair);
  color_list = list_create (color);

  init_pair (pair->idx, pair->fg, pair->bg);
}