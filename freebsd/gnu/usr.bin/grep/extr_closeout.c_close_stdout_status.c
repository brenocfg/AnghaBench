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
 char* _ (char*) ; 
 scalar_t__ __fpending (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  error (int,int,char*,char const*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ file_name ; 
 char* quotearg_colon (scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 

void
close_stdout_status (int status)
{
  int e = ferror (stdout) ? 0 : -1;

#if 0
  if (__fpending (stdout) == 0)
    return;
#endif

  if (fclose (stdout) != 0)
    e = errno;

  if (0 < e)
    {
      char const *write_error = _("write error");
      if (file_name)
	error (status, e, "%s: %s", quotearg_colon (file_name), write_error);
      else
	error (status, e, "%s", write_error);
    }
}