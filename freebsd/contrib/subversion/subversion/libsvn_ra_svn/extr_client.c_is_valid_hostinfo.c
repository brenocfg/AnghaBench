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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strchr (char*,char const) ; 
 int /*<<< orphan*/  svn_ctype_isalnum (char const) ; 

__attribute__((used)) static svn_boolean_t
is_valid_hostinfo(const char *hostinfo)
{
  const char *p = hostinfo;

  if (p[0] == '-')
    return FALSE;

  while (*p)
    {
      if (!svn_ctype_isalnum(*p) && !strchr(":.-_[]@", *p))
        return FALSE;

      ++p;
    }

  return TRUE;
}