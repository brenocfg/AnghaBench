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
struct ui_file {int dummy; } ;
struct accumulated_ui_file {char* buffer; long length; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_ui_file_xstrdup ; 
 int /*<<< orphan*/  ui_file_put (struct ui_file*,int /*<<< orphan*/ ,struct accumulated_ui_file*) ; 
 char* xstrdup (char*) ; 

char *
ui_file_xstrdup (struct ui_file *file,
		  long *length)
{
  struct accumulated_ui_file acc;
  acc.buffer = NULL;
  acc.length = 0;
  ui_file_put (file, do_ui_file_xstrdup, &acc);
  if (acc.buffer == NULL)
    acc.buffer = xstrdup ("");
  *length = acc.length;
  return acc.buffer;
}