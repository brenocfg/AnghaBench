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
typedef  int /*<<< orphan*/  ui_file_write_ftype ;
struct ui_file {int /*<<< orphan*/ * to_write; } ;

/* Variables and functions */

void
set_ui_file_write (struct ui_file *file,
		    ui_file_write_ftype *write)
{
  file->to_write = write;
}