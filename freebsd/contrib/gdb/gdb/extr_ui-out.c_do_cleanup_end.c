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
struct ui_out_end_cleanup_data {int /*<<< orphan*/  type; int /*<<< orphan*/  uiout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ui_out_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct ui_out_end_cleanup_data*) ; 

__attribute__((used)) static void
do_cleanup_end (void *data)
{
  struct ui_out_end_cleanup_data *end_cleanup_data = data;
  ui_out_end (end_cleanup_data->uiout, end_cleanup_data->type);
  xfree (end_cleanup_data);
}