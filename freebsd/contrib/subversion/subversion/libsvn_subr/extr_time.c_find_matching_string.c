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
typedef  size_t apr_size_t ;
typedef  int apr_int32_t ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static apr_int32_t
find_matching_string(char *str, apr_size_t size, const char strings[][4])
{
  apr_size_t i;

  for (i = 0; i < size; i++)
    if (strings[i] && (strcmp(str, strings[i]) == 0))
      return (apr_int32_t) i;

  return -1;
}