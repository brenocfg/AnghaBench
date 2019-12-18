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
typedef  enum ui_out_type { ____Placeholder_ui_out_type } ui_out_type ;

/* Variables and functions */

__attribute__((used)) static void
default_end (struct ui_out *uiout,
	     enum ui_out_type type,
	     int level)
{
}