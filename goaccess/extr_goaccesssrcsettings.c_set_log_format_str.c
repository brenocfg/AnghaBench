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
struct TYPE_2__ {char* log_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_log_format_item_enum (char const*) ; 
 char* get_selected_format_str (int) ; 
 int /*<<< orphan*/  set_date_format_str (char const*) ; 
 int /*<<< orphan*/  set_time_format_str (char const*) ; 
 void* unescape_str (char const*) ; 

void
set_log_format_str (const char *oarg)
{
  char *fmt = NULL;
  int type = get_log_format_item_enum (oarg);

  /* free log format if it was previously set */
  if (conf.log_format)
    free (conf.log_format);

  /* type not found, use whatever was given by the user then */
  if (type == -1) {
    conf.log_format = unescape_str (oarg);
    return;
  }

  /* attempt to get the format string by the enum value */
  if ((fmt = get_selected_format_str (type)) == NULL) {
    LOG_DEBUG (("Unable to set log format from enum: %s\n", oarg));
    return;
  }

  conf.log_format = unescape_str (fmt);
  /* assume we are using the default date/time formats */
  set_time_format_str (oarg);
  set_date_format_str (oarg);
  free (fmt);
}