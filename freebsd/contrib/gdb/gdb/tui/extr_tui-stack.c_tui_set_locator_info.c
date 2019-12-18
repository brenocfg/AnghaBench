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
struct tui_locator_element {char* proc_name; int line_no; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {struct tui_locator_element locator; } ;
struct tui_win_element {TYPE_1__ which_element; } ;
struct tui_gen_win_info {int content_size; void** content; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LOCATOR_ELEMENT_LEN ; 
 int /*<<< orphan*/  strcat_to_buf (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ tui_alloc_content (int,int /*<<< orphan*/ ) ; 
 struct tui_gen_win_info* tui_locator_win_info_ptr () ; 
 int /*<<< orphan*/  tui_set_locator_filename (char const*) ; 

__attribute__((used)) static void
tui_set_locator_info (const char *filename, const char *procname, int lineno,
                      CORE_ADDR addr)
{
  struct tui_gen_win_info * locator = tui_locator_win_info_ptr ();
  struct tui_locator_element * element;

  /* Allocate the locator content if necessary.  */
  if (locator->content_size <= 0)
    {
      locator->content = (void **) tui_alloc_content (1, locator->type);
      locator->content_size = 1;
    }

  element = &((struct tui_win_element *) locator->content[0])->which_element.locator;
  element->proc_name[0] = (char) 0;
  strcat_to_buf (element->proc_name, MAX_LOCATOR_ELEMENT_LEN, procname);
  element->line_no = lineno;
  element->addr = addr;
  tui_set_locator_filename (filename);
}