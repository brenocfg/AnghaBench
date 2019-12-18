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
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

const char *
svn_cstring_skip_prefix(const char *str, const char *prefix)
{
  apr_size_t len = strlen(prefix);

  if (strncmp(str, prefix, len) == 0)
    {
      return str + len;
    }
  else
    {
      return NULL;
    }
}