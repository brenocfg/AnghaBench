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
struct value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_value_equal (struct value*,struct value*,int*) ; 

__attribute__((used)) static int
my_value_equal (struct value *val1, struct value *val2, int *error2)
{
  int r, err1, err2;

  *error2 = 0;
  /* Special case: NULL values. If both are null, say
     they're equal. */
  if (val1 == NULL && val2 == NULL)
    return 1;
  else if (val1 == NULL || val2 == NULL)
    return 0;

  /* This is bogus, but unfortunately necessary. We must know
     exactly what caused an error -- reading val1 or val2 --  so
     that we can really determine if we think that something has changed. */
  err1 = 0;
  err2 = 0;
  /* We do need to catch errors here because the whole purpose
     is to test if value_equal() has errored */
  if (!gdb_value_equal (val1, val1, &r))
    err1 = 1;

  if (!gdb_value_equal (val2, val2, &r))
    *error2 = err2 = 1;

  if (err1 != err2)
    return 0;

  if (!gdb_value_equal (val1, val2, &r))
    {
      /* An error occurred, this could have happened if
         either val1 or val2 errored. ERR1 and ERR2 tell
         us which of these it is. If both errored, then
         we assume nothing has changed. If one of them is
         valid, though, then something has changed. */
      if (err1 == err2)
	{
	  /* both the old and new values caused errors, so
	     we say the value did not change */
	  /* This is indeterminate, though. Perhaps we should
	     be safe and say, yes, it changed anyway?? */
	  return 1;
	}
      else
	{
	  return 0;
	}
    }

  return r;
}