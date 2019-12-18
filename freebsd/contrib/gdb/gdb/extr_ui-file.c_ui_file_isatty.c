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
struct ui_file {int (* to_isatty ) (struct ui_file*) ;} ;

/* Variables and functions */
 int stub1 (struct ui_file*) ; 

int
ui_file_isatty (struct ui_file *file)
{
  return file->to_isatty (file);
}