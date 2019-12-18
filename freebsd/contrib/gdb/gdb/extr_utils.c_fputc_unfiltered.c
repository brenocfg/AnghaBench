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

/* Variables and functions */
 int /*<<< orphan*/  ui_file_write (struct ui_file*,char*,int) ; 

int
fputc_unfiltered (int c, struct ui_file *stream)
{
  char buf = c;
  ui_file_write (stream, &buf, 1);
  return c;
}