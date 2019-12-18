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
 scalar_t__ alloca (scalar_t__) ; 
 int /*<<< orphan*/  bfd_error_no_error ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void
perror_with_name (const char *string)
{
  char *err;
  char *combined;

  err = safe_strerror (errno);
  combined = (char *) alloca (strlen (err) + strlen (string) + 3);
  strcpy (combined, string);
  strcat (combined, ": ");
  strcat (combined, err);

  /* I understand setting these is a matter of taste.  Still, some people
     may clear errno but not know about bfd_error.  Doing this here is not
     unreasonable. */
  bfd_set_error (bfd_error_no_error);
  errno = 0;

  error ("%s.", combined);
}