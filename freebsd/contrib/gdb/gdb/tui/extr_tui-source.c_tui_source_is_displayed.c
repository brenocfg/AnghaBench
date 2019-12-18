#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  file_name; } ;
struct TYPE_8__ {TYPE_2__ locator; } ;
struct tui_win_element {TYPE_3__ which_element; } ;
struct TYPE_6__ {scalar_t__ content_in_use; } ;
struct TYPE_10__ {TYPE_1__ generic; } ;
struct TYPE_9__ {scalar_t__* content; } ;

/* Variables and functions */
 TYPE_5__* TUI_SRC_WIN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* tui_locator_win_info_ptr () ; 

int
tui_source_is_displayed (char *fname)
{
  return (TUI_SRC_WIN->generic.content_in_use &&
	  (strcmp (((struct tui_win_element *) (tui_locator_win_info_ptr ())->
		  content[0])->which_element.locator.file_name, fname) == 0));
}