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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,int,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char *
print_two_power(int i,
                apr_pool_t *result_pool)
{
  /* These are the SI prefixes for base-1000, the binary ones with base-1024
     are too clumsy and require appending B for "byte" to be intelligible,
     e.g. "MiB".

     Therefore, we ignore the official standard and revert to the traditional
     contextual use were the base-1000 prefixes are understood as base-1024
     when it came to data sizes.
   */
  const char *si_prefixes = " kMGTPEZY";

  int number = (i >= 0) ? (1 << (i % 10)) : 0;
  int thousands = (i >= 0) ? (i / 10) : 0;

  char si_prefix = (thousands < strlen(si_prefixes))
                 ? si_prefixes[thousands]
                 : '?';

  if (si_prefix == ' ')
    return apr_psprintf(result_pool, "%d", number);

  return apr_psprintf(result_pool, "%d%c", number, si_prefix);
}