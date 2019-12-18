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
struct tui_win_element {int dummy; } ;
struct tui_gen_win_info {void** content; int content_size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_content_element (struct tui_win_element*,int /*<<< orphan*/ ) ; 
 scalar_t__ tui_alloc_content (int,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

int
tui_add_content_elements (struct tui_gen_win_info * win_info, int num_elements)
{
  struct tui_win_element * element_ptr;
  int i, index_start;

  if (win_info->content == NULL)
    {
      win_info->content = (void **) tui_alloc_content (num_elements, win_info->type);
      index_start = 0;
    }
  else
    index_start = win_info->content_size;
  if (win_info->content != NULL)
    {
      for (i = index_start; (i < num_elements + index_start); i++)
	{
	  if ((element_ptr = (struct tui_win_element *)
	       xmalloc (sizeof (struct tui_win_element))) != (struct tui_win_element *) NULL)
	    {
	      win_info->content[i] = (void *) element_ptr;
	      init_content_element (element_ptr, win_info->type);
	      win_info->content_size++;
	    }
	  else			/* things must be really hosed now! We ran out of memory!? */
	    return (-1);
	}
    }

  return index_start;
}