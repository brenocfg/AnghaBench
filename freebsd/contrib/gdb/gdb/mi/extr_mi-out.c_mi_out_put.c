#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ui_out {int dummy; } ;
struct ui_file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ mi_out_data ;

/* Variables and functions */
 int /*<<< orphan*/  do_write ; 
 int /*<<< orphan*/  ui_file_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  ui_file_rewind (int /*<<< orphan*/ ) ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 

void
mi_out_put (struct ui_out *uiout,
	    struct ui_file *stream)
{
  mi_out_data *data = ui_out_data (uiout);
  ui_file_put (data->buffer, do_write, stream);
  ui_file_rewind (data->buffer);
}