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
 int PARSE_NOHASH ; 
 int PARSE_REDUCE ; 
 scalar_t__ issep (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

char *
findblank(char *p, int flags)
{
  int instring;

  instring = 0;
  while (*p) {
    if (*p == '\\') {
      if (flags & PARSE_REDUCE) {
        memmove(p, p + 1, strlen(p));
        if (!*p)
          break;
      } else
        p++;
    } else if (*p == '"') {
      memmove(p, p + 1, strlen(p));
      instring = !instring;
      continue;
    } else if (!instring && (issep(*p) ||
                             (*p == '#' && !(flags & PARSE_NOHASH))))
      return p;
    p++;
  }

  return instring ? NULL : p;
}