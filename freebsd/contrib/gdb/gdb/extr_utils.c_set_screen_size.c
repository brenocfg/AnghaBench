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

/* Variables and functions */
 int INT_MAX ; 
 int chars_per_line ; 
 int lines_per_page ; 
 int /*<<< orphan*/  rl_get_screen_size (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rl_set_screen_size (int,int) ; 

__attribute__((used)) static void
set_screen_size (void)
{
  int rows = lines_per_page;
  int cols = chars_per_line;

  if (rows <= 0)
    rows = INT_MAX;

  if (cols <= 0)
    rl_get_screen_size (NULL, &cols);

  /* Update Readline's idea of the terminal size.  */
  rl_set_screen_size (rows, cols);
}