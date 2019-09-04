#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* spec_date_time_num_format; } ;
struct TYPE_5__ {int idx; } ;
typedef  TYPE_1__ GHolder ;

/* Variables and functions */
 int VISITORS ; 
 TYPE_4__ conf ; 
 int /*<<< orphan*/  free (char**) ; 
 char* get_visitors_date (char*,char const*,char const*) ; 
 char** get_visitors_dates (TYPE_1__*) ; 

int
get_start_end_parsing_dates (GHolder * h, char **start, char **end,
                             const char *f)
{
  char **dates = NULL;
  const char *sndfmt = conf.spec_date_time_num_format;

  if (h->idx == 0)
    return 1;

  dates = get_visitors_dates (h + VISITORS);

  /* just display the actual dates - no specificity */
  *start = get_visitors_date (dates[0], sndfmt, f);
  *end = get_visitors_date (dates[h->idx - 1], sndfmt, f);

  free (dates);

  return 0;
}