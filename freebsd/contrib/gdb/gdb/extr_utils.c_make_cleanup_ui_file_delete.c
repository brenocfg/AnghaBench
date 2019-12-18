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
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_chain ; 
 int /*<<< orphan*/  do_ui_file_delete ; 
 struct cleanup* make_my_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ui_file*) ; 

struct cleanup *
make_cleanup_ui_file_delete (struct ui_file *arg)
{
  return make_my_cleanup (&cleanup_chain, do_ui_file_delete, arg);
}