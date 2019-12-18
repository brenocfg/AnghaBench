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
struct TYPE_2__ {int /*<<< orphan*/  time_format; int /*<<< orphan*/  date_format; } ;

/* Variables and functions */
 char* clean_date_time_format (int /*<<< orphan*/ ) ; 
 TYPE_1__ conf ; 
 scalar_t__ has_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
set_format_time (void)
{
  char *ftime = NULL;

  if (has_timestamp (conf.date_format) || !strcmp ("%T", conf.time_format))
    ftime = xstrdup ("%H%M%S");
  else
    ftime = clean_date_time_format (conf.time_format);

  return ftime;
}