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

/* Variables and functions */
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
clean_date_time_format (const char *format)
{
  char *fmt = NULL, *pr = NULL, *pw = NULL;
  int special = 0;

  if (format == NULL || *format == '\0')
    return NULL;

  fmt = xstrdup (format);
  pr = fmt;
  pw = fmt;
  while (*pr) {
    *pw = *pr++;
    if (*pw == '%' || special) {
      special = !special;
      pw++;
    }
  }
  *pw = '\0';

  return fmt;
}