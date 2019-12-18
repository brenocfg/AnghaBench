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
struct symtab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  select_source_symtab (struct symtab*) ; 
 int /*<<< orphan*/  tui_show_frame_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tui_print_frame_info_listing_hook (struct symtab *s, int line,
                                   int stopline, int noerror)
{
  select_source_symtab (s);
  tui_show_frame_info (deprecated_selected_frame);
}