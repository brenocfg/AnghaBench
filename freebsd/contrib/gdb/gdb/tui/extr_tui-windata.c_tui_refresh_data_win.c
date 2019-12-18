#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ content_size; } ;
struct TYPE_4__ {TYPE_1__ generic; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* TUI_DATA_WIN ; 
 int /*<<< orphan*/  tui_display_data_from (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_erase_data_content (char*) ; 
 int tui_first_data_item_displayed () ; 

void
tui_refresh_data_win (void)
{
  tui_erase_data_content ((char *) NULL);
  if (TUI_DATA_WIN->generic.content_size > 0)
    {
      int first_element = tui_first_data_item_displayed ();

      if (first_element >= 0)	/* re-use existing windows */
	tui_display_data_from (first_element, TRUE);
    }
}