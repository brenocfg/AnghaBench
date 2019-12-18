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
struct TYPE_2__ {int filenames_idx; char** filenames; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_str (char**,char*) ; 
 TYPE_1__ conf ; 
 int strlen (char*) ; 
 char* xstrdup (char*) ; 

char *
get_log_source_str (int max_len)
{
  char *str = xstrdup ("");
  int i, len = 0;

  for (i = 0; i < conf.filenames_idx; ++i) {
    if (conf.filenames[i][0] == '-' && conf.filenames[i][1] == '\0')
      append_str (&str, "STDIN");
    else
      append_str (&str, conf.filenames[i]);
    if (i != conf.filenames_idx - 1)
      append_str (&str, "; ");
  }

  len = strlen (str);
  if (max_len > 0 && len > 0 && len > max_len) {
    str[max_len - 3] = 0;
    append_str (&str, "...");
  }

  return str;
}