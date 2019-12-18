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
typedef  int apr_size_t ;

/* Variables and functions */

void
svn_authz__reverse_string(char *string, apr_size_t len)
{
  char *left = string;
  char *right = string + len - 1;
  for (; left < right; ++left, --right)
    {
      char c = *left;
      *left = *right;
      *right = c;
    }
}