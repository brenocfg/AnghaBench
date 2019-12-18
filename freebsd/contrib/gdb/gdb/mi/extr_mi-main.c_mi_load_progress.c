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
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERP_MI ; 
 int /*<<< orphan*/  INTERP_MI1 ; 
 int /*<<< orphan*/  current_interp_named_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 char* last_async_command ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mi_out_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_stdout ; 
 int strcmp (char*,char const*) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char const*) ; 

void
mi_load_progress (const char *section_name,
		  unsigned long sent_so_far,
		  unsigned long total_section,
		  unsigned long total_sent,
		  unsigned long grand_total)
{
  struct timeval time_now, delta, update_threshold;
  static struct timeval last_update;
  static char *previous_sect_name = NULL;
  int new_section;

  if (!current_interp_named_p (INTERP_MI)
      && !current_interp_named_p (INTERP_MI1))
    return;

  update_threshold.tv_sec = 0;
  update_threshold.tv_usec = 500000;
  gettimeofday (&time_now, NULL);

  delta.tv_usec = time_now.tv_usec - last_update.tv_usec;
  delta.tv_sec = time_now.tv_sec - last_update.tv_sec;

  if (delta.tv_usec < 0)
    {
      delta.tv_sec -= 1;
      delta.tv_usec += 1000000;
    }

  new_section = (previous_sect_name ?
		 strcmp (previous_sect_name, section_name) : 1);
  if (new_section)
    {
      struct cleanup *cleanup_tuple;
      xfree (previous_sect_name);
      previous_sect_name = xstrdup (section_name);

      if (last_async_command)
	fputs_unfiltered (last_async_command, raw_stdout);
      fputs_unfiltered ("+download", raw_stdout);
      cleanup_tuple = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
      ui_out_field_string (uiout, "section", section_name);
      ui_out_field_int (uiout, "section-size", total_section);
      ui_out_field_int (uiout, "total-size", grand_total);
      do_cleanups (cleanup_tuple);
      mi_out_put (uiout, raw_stdout);
      fputs_unfiltered ("\n", raw_stdout);
      gdb_flush (raw_stdout);
    }

  if (delta.tv_sec >= update_threshold.tv_sec &&
      delta.tv_usec >= update_threshold.tv_usec)
    {
      struct cleanup *cleanup_tuple;
      last_update.tv_sec = time_now.tv_sec;
      last_update.tv_usec = time_now.tv_usec;
      if (last_async_command)
	fputs_unfiltered (last_async_command, raw_stdout);
      fputs_unfiltered ("+download", raw_stdout);
      cleanup_tuple = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
      ui_out_field_string (uiout, "section", section_name);
      ui_out_field_int (uiout, "section-sent", sent_so_far);
      ui_out_field_int (uiout, "section-size", total_section);
      ui_out_field_int (uiout, "total-sent", total_sent);
      ui_out_field_int (uiout, "total-size", grand_total);
      do_cleanups (cleanup_tuple);
      mi_out_put (uiout, raw_stdout);
      fputs_unfiltered ("\n", raw_stdout);
      gdb_flush (raw_stdout);
    }
}