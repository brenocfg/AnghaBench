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
struct TYPE_2__ {char* date_num_format; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_date_abbreviated (char*) ; 
 char* set_format_date () ; 
 scalar_t__ snprintf (char*,int,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strpbrk (char*,char*) ; 
 char* xcalloc (int,int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
set_date_num_format (void)
{
  char *fdate = NULL, *buf = NULL;
  int buflen = 0, flen = 0;

  fdate = set_format_date ();
  if (!fdate)
    return 1;

  if (is_date_abbreviated (fdate)) {
    free (fdate);
    conf.date_num_format = xstrdup ("%Y%m%d");
    return 0;
  }

  flen = strlen (fdate) + 1;
  buf = xcalloc (flen, sizeof (char));

  if (strpbrk (fdate, "Yy"))
    buflen += snprintf (buf + buflen, flen - buflen, "%%Y");
  if (strpbrk (fdate, "hbmB"))
    buflen += snprintf (buf + buflen, flen - buflen, "%%m");
  if (strpbrk (fdate, "de"))
    buflen += snprintf (buf + buflen, flen - buflen, "%%d");

  conf.date_num_format = buf;
  free (fdate);

  return buflen == 0 ? 1 : 0;
}