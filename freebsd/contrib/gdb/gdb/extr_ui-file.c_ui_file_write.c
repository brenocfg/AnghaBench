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
struct ui_file {int /*<<< orphan*/  (* to_write ) (struct ui_file*,char const*,long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_file*,char const*,long) ; 

void
ui_file_write (struct ui_file *file,
		const char *buf,
		long length_buf)
{
  file->to_write (file, buf, length_buf);
}