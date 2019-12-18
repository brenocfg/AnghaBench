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
 unsigned long long DAY ; 
 unsigned long long HOUR ; 
 unsigned long long MILS ; 
 unsigned long long MINS ; 
 unsigned long long SECS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 
 char* xmalloc (int) ; 

char *
usecs_to_str (unsigned long long usec)
{
  char *size = xmalloc (sizeof (char) * 11);
  if (usec >= DAY)
    snprintf (size, 11, "%.2f  d", (double) (usec) / DAY);
  else if (usec >= HOUR)
    snprintf (size, 11, "%.2f hr", (double) (usec) / HOUR);
  else if (usec >= MINS)
    snprintf (size, 11, "%.2f mn", (double) (usec) / MINS);
  else if (usec >= SECS)
    snprintf (size, 11, "%.2f  s", (double) (usec) / SECS);
  else if (usec >= MILS)
    snprintf (size, 11, "%.2f ms", (double) (usec) / MILS);
  else
    snprintf (size, 11, "%.2f us", (double) (usec));

  return size;
}