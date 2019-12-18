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
struct ui_file {int /*<<< orphan*/  (* to_delete ) (struct ui_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_file*) ; 
 int /*<<< orphan*/  xfree (struct ui_file*) ; 

void
ui_file_delete (struct ui_file *file)
{
  file->to_delete (file);
  xfree (file);
}