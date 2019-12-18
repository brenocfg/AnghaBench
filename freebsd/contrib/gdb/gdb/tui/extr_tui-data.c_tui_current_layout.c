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
typedef  enum tui_layout_type { ____Placeholder_tui_layout_type } tui_layout_type ;

/* Variables and functions */
 int current_layout ; 

enum tui_layout_type
tui_current_layout (void)
{
  return current_layout;
}