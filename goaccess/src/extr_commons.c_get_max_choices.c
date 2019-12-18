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
struct TYPE_2__ {int max_items; scalar_t__ output_format_idx; scalar_t__ real_time_html; int /*<<< orphan*/  output_stdout; } ;

/* Variables and functions */
 int MAX_CHOICES ; 
 int MAX_CHOICES_RT ; 
 TYPE_1__ conf ; 
 scalar_t__ find_output_type (char**,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 

int
get_max_choices (void)
{
  char *csv = NULL, *json = NULL, *html = NULL;
  int max = MAX_CHOICES;

  /* no max choices, return defaults */
  if (conf.max_items <= 0)
    return conf.real_time_html ? MAX_CHOICES_RT : MAX_CHOICES;

  /* TERM */
  if (!conf.output_stdout)
    return conf.max_items > MAX_CHOICES ? MAX_CHOICES : conf.max_items;

  /* REAL-TIME STDOUT */
  /* real time HTML, display max rt choices */
  if (conf.real_time_html)
    return conf.max_items > MAX_CHOICES_RT ? MAX_CHOICES_RT : conf.max_items;

  /* STDOUT */
  /* CSV - allow n amount of choices */
  if (find_output_type (&csv, "csv", 1) == 0)
    max = conf.max_items;
  /* JSON - allow n amount of choices */
  if (find_output_type (&json, "json", 1) == 0 && conf.max_items > 0)
    max = conf.max_items;
  /* HTML - takes priority on cases where multiple outputs were given. Note that
   * we check either for an .html extension or we assume not extension was passed
   * via -o and therefore we are redirecting the output to a file. */
  if (find_output_type (&html, "html", 1) == 0 || conf.output_format_idx == 0)
    max = conf.max_items > MAX_CHOICES ? MAX_CHOICES : conf.max_items;

  free (csv);
  free (html);
  free (json);

  return max;
}