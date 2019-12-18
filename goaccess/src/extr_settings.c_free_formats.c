#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  time_format; int /*<<< orphan*/  spec_date_time_num_format; int /*<<< orphan*/  spec_date_time_format; int /*<<< orphan*/  date_num_format; int /*<<< orphan*/  date_format; int /*<<< orphan*/  log_format; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
free_formats (void)
{
  free (conf.log_format);
  free (conf.date_format);
  free (conf.date_num_format);
  free (conf.spec_date_time_format);
  free (conf.spec_date_time_num_format);
  free (conf.time_format);
}