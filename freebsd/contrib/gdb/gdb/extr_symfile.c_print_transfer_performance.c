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
 int /*<<< orphan*/  ui_out_field_fmt (int /*<<< orphan*/ ,char*,char*,unsigned long) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 

void
print_transfer_performance (struct ui_file *stream,
			    unsigned long data_count,
			    unsigned long write_count,
			    unsigned long time_count)
{
  ui_out_text (uiout, "Transfer rate: ");
  if (time_count > 0)
    {
      ui_out_field_fmt (uiout, "transfer-rate", "%lu", 
			(data_count * 8) / time_count);
      ui_out_text (uiout, " bits/sec");
    }
  else
    {
      ui_out_field_fmt (uiout, "transferred-bits", "%lu", (data_count * 8));
      ui_out_text (uiout, " bits in <1 sec");    
    }
  if (write_count > 0)
    {
      ui_out_text (uiout, ", ");
      ui_out_field_fmt (uiout, "write-rate", "%lu", data_count / write_count);
      ui_out_text (uiout, " bytes/write");
    }
  ui_out_text (uiout, ".\n");
}