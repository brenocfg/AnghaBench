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
typedef  int /*<<< orphan*/  ui_file_fputs_ftype ;
struct ui_file {int /*<<< orphan*/ * to_fputs; } ;

/* Variables and functions */

void
set_ui_file_fputs (struct ui_file *file, ui_file_fputs_ftype *fputs)
{
  file->to_fputs = fputs;
}