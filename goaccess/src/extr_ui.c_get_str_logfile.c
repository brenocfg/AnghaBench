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
 char* get_log_source_str (int) ; 
 int getmaxx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdscr ; 

__attribute__((used)) static char *
get_str_logfile (void)
{
  int col = getmaxx (stdscr), left_padding = 20;
  return get_log_source_str (col - left_padding);
}