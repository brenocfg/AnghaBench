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
struct TYPE_2__ {int /*<<< orphan*/  spec_date_time_format; int /*<<< orphan*/  spec_date_time_num_format; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 char* get_visitors_date (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
set_visitors_date (const char *value)
{
  return get_visitors_date (value, conf.spec_date_time_num_format,
                            conf.spec_date_time_format);
}