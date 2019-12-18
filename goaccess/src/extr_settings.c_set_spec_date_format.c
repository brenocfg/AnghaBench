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
struct TYPE_2__ {scalar_t__ spec_date_time_num_format; scalar_t__ spec_date_time_format; scalar_t__ date_num_format; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ set_date_num_format () ; 
 int /*<<< orphan*/  set_spec_date_time_format () ; 
 int /*<<< orphan*/  set_spec_date_time_num_format () ; 
 scalar_t__ verify_formats () ; 

void
set_spec_date_format (void)
{
  if (verify_formats ())
    return;

  if (conf.date_num_format)
    free (conf.date_num_format);
  if (conf.spec_date_time_format)
    free (conf.spec_date_time_format);
  if (conf.spec_date_time_num_format)
    free (conf.spec_date_time_num_format);

  if (set_date_num_format () == 0) {
    set_spec_date_time_num_format ();
    set_spec_date_time_format ();
  }
}