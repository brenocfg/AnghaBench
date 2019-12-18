#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int width; int height; int content_size; scalar_t__* content; } ;
struct tui_win_info {TYPE_1__ generic; } ;
struct TYPE_6__ {scalar_t__ line_no; } ;
struct TYPE_7__ {char* line; void* has_break; void* is_exec_point; TYPE_2__ line_or_addr; } ;
struct TYPE_8__ {TYPE_3__ source; } ;
struct tui_win_element {TYPE_4__ which_element; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 

void
tui_set_source_content_nil (struct tui_win_info * win_info, char *warning_string)
{
  int line_width;
  int n_lines;
  int curr_line = 0;

  line_width = win_info->generic.width - 1;
  n_lines = win_info->generic.height - 2;

  /* set to empty each line in the window, except for the one
     which contains the message */
  while (curr_line < win_info->generic.content_size)
    {
      /* set the information related to each displayed line
         to null: i.e. the line number is 0, there is no bp,
         it is not where the program is stopped */

      struct tui_win_element * element =
      (struct tui_win_element *) win_info->generic.content[curr_line];
      element->which_element.source.line_or_addr.line_no = 0;
      element->which_element.source.is_exec_point = FALSE;
      element->which_element.source.has_break = FALSE;

      /* set the contents of the line to blank */
      element->which_element.source.line[0] = (char) 0;

      /* if the current line is in the middle of the screen, then we
         want to display the 'no source available' message in it.
         Note: the 'weird' arithmetic with the line width and height
         comes from the function tui_erase_source_content(). We need
         to keep the screen and the window's actual contents in synch.  */

      if (curr_line == (n_lines / 2 + 1))
	{
	  int i;
	  int xpos;
	  int warning_length = strlen (warning_string);
	  char *src_line;

	  src_line = element->which_element.source.line;

	  if (warning_length >= ((line_width - 1) / 2))
	    xpos = 1;
	  else
	    xpos = (line_width - 1) / 2 - warning_length;

	  for (i = 0; i < xpos; i++)
	    src_line[i] = ' ';

	  sprintf (src_line + i, "%s", warning_string);

	  for (i = xpos + warning_length; i < line_width; i++)
	    src_line[i] = ' ';

	  src_line[i] = '\n';

	}			/* end if */

      curr_line++;

    }				/* end while */
}