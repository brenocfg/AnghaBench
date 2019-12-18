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
struct tui_locator_element {scalar_t__* file_name; } ;
struct TYPE_2__ {struct tui_locator_element locator; } ;
struct tui_win_element {TYPE_1__ which_element; } ;
struct tui_gen_win_info {int /*<<< orphan*/ ** content; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LOCATOR_ELEMENT_LEN ; 
 int /*<<< orphan*/  strcat_to_buf (scalar_t__*,int /*<<< orphan*/ ,char const*) ; 
 struct tui_gen_win_info* tui_locator_win_info_ptr () ; 
 int /*<<< orphan*/  tui_set_locator_info (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tui_set_locator_filename (const char *filename)
{
  struct tui_gen_win_info * locator = tui_locator_win_info_ptr ();
  struct tui_locator_element * element;

  if (locator->content[0] == NULL)
    {
      tui_set_locator_info (filename, NULL, 0, 0);
      return;
    }

  element = &((struct tui_win_element *) locator->content[0])->which_element.locator;
  element->file_name[0] = 0;
  strcat_to_buf (element->file_name, MAX_LOCATOR_ELEMENT_LEN, filename);
}