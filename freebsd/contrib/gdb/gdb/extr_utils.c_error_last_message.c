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
 int /*<<< orphan*/  gdb_lasterr ; 
 char* ui_file_xstrdup (int /*<<< orphan*/ ,long*) ; 

char *
error_last_message (void)
{
  long len;
  return ui_file_xstrdup (gdb_lasterr, &len);
}