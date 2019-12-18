#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {char const* data; } ;

/* Variables and functions */
 TYPE_1__* svn_string_ncreate (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
next_line(const char **str, apr_pool_t *pool)
{
  const char *start = *str;
  const char *p = *str;

  /* n.b. Throughout this fn, we never read any character after a '\0'. */
  /* Skip over all non-EOL characters, if any. */
  while (*p != '\r' && *p != '\n' && *p != '\0')
    p++;
  /* Skip over \r\n or \n\r or \r or \n, if any. */
  if (*p == '\r' || *p == '\n')
    {
      char c = *p++;

      if ((c == '\r' && *p == '\n') || (c == '\n' && *p == '\r'))
        p++;
    }

  /* Now p points after at most one '\n' and/or '\r'. */
  *str = p;

  if (p == start)
    return NULL;

  return svn_string_ncreate(start, p - start, pool)->data;
}