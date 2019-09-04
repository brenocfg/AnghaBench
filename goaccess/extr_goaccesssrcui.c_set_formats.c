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
struct TYPE_2__ {void* log_format; void* date_format; void* time_format; } ;

/* Variables and functions */
 char const* ERR_FORMAT_NO_DATE_FMT_DLG ; 
 char const* ERR_FORMAT_NO_LOG_FMT_DLG ; 
 char const* ERR_FORMAT_NO_TIME_FMT_DLG ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  set_spec_date_format () ; 
 void* unescape_str (char*) ; 

__attribute__((used)) static const char *
set_formats (char *date_format, char *log_format, char *time_format)
{
  /* display status bar error messages */
  if (!time_format && !conf.time_format)
    return ERR_FORMAT_NO_TIME_FMT_DLG;
  if (!date_format && !conf.date_format)
    return ERR_FORMAT_NO_DATE_FMT_DLG;
  if (!log_format && !conf.log_format)
    return ERR_FORMAT_NO_LOG_FMT_DLG;

  if (time_format) {
    free (conf.time_format);
    conf.time_format = unescape_str (time_format);
  }

  if (date_format) {
    free (conf.date_format);
    conf.date_format = unescape_str (date_format);
  }

  if (log_format) {
    free (conf.log_format);
    conf.log_format = unescape_str (log_format);
  }

  set_spec_date_format ();

  return NULL;
}