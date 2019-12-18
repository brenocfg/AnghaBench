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
 int APR_ENOMEM ; 
 int /*<<< orphan*/  EXCEPTION_NONCONTINUABLE ; 
 int /*<<< orphan*/  RaiseException (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
abort_on_pool_failure(int retcode)
{
  /* Don't translate this string! It requires memory allocation to do so!
     And we don't have any of it... */
  printf("libsvn: Out of memory - terminating application.\n");

#ifdef WIN32
  /* Provide a way to distinguish the out-of-memory error from abort(). */
  if (retcode == APR_ENOMEM)
    RaiseException(STATUS_NO_MEMORY, EXCEPTION_NONCONTINUABLE, 0, NULL);
#endif

  abort();
  return 0; /* not reached */
}