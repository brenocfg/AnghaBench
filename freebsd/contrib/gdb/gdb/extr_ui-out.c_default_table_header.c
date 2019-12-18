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
struct ui_out {int dummy; } ;
typedef  enum ui_align { ____Placeholder_ui_align } ui_align ;

/* Variables and functions */

__attribute__((used)) static void
default_table_header (struct ui_out *uiout, int width, enum ui_align alignment,
		      const char *col_name,
		      const char *colhdr)
{
}