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
typedef  int /*<<< orphan*/  threadref ;

/* Variables and functions */

__attribute__((used)) static int
threadmatch (threadref *dest, threadref *src)
{
  /* things are broken right now, so just assume we got a match */
#if 0
  unsigned char *srcp, *destp;
  int i, result;
  srcp = (char *) src;
  destp = (char *) dest;

  result = 1;
  while (i-- > 0)
    result &= (*srcp++ == *destp++) ? 1 : 0;
  return result;
#endif
  return 1;
}