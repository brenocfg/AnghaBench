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
typedef  scalar_t__ tui_win_content ;
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;

/* Variables and functions */
 int /*<<< orphan*/  free_content_elements (scalar_t__,int,int) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

__attribute__((used)) static void
free_content (tui_win_content content, int content_size, enum tui_win_type win_type)
{
  if (content != (tui_win_content) NULL)
    {
      free_content_elements (content, content_size, win_type);
      xfree (content);
    }
}