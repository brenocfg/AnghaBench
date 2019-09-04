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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ ETA_ABSOLUTE_MAX_EXCEEDED ; 
 char* ctime_r (scalar_t__*,char*) ; 
 int overflow_check_u64_add (scalar_t__,scalar_t__) ; 
 scalar_t__ status_get_sec_etc (int /*<<< orphan*/  const*) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

char *status_get_time_estimated_absolute (const hashcat_ctx_t *hashcat_ctx)
{
  time_t sec_etc = status_get_sec_etc (hashcat_ctx);

  time_t now;
  time (&now);


  char buf[32] = { 0 };

  char *etc;

  if (overflow_check_u64_add (now, sec_etc) == false)
  {
    etc = (char *) ETA_ABSOLUTE_MAX_EXCEEDED;
  }
  else
  {
    time_t end = now + sec_etc;

    etc = ctime_r (&end, buf);

    if (etc == NULL) etc = (char *) ETA_ABSOLUTE_MAX_EXCEEDED;
  }

  const size_t etc_len = strlen (etc);

  if (etc[etc_len - 1] == '\n') etc[etc_len - 1] = 0;
  if (etc[etc_len - 2] == '\r') etc[etc_len - 2] = 0;

  return strdup (etc);
}