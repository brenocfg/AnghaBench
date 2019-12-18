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
struct TYPE_2__ {int /*<<< orphan*/  locator; } ;
struct tui_win_element {TYPE_1__ which_element; } ;
struct tui_gen_win_info {int /*<<< orphan*/  content_in_use; int /*<<< orphan*/ * handle; scalar_t__* content; } ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 struct tui_gen_win_info* tui_locator_win_info_ptr () ; 
 char* tui_make_status_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tui_refresh_win (struct tui_gen_win_info*) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wstandend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wstandout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
tui_show_locator_content (void)
{
  char *string;
  struct tui_gen_win_info * locator;

  locator = tui_locator_win_info_ptr ();

  if (locator != NULL && locator->handle != (WINDOW *) NULL)
    {
      struct tui_win_element * element;

      element = (struct tui_win_element *) locator->content[0];

      string = tui_make_status_line (&element->which_element.locator);
      wmove (locator->handle, 0, 0);
      wstandout (locator->handle);
      waddstr (locator->handle, string);
      wclrtoeol (locator->handle);
      wstandend (locator->handle);
      tui_refresh_win (locator);
      wmove (locator->handle, 0, 0);
      xfree (string);
      locator->content_in_use = TRUE;
    }
}