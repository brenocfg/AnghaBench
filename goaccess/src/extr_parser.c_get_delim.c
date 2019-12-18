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

__attribute__((used)) static int
get_delim (char *dest, const char *p)
{
  /* done, nothing to do */
  if (p[0] == '\0' || p[1] == '\0') {
    dest[0] = '\0';
    return 0;
  }
  /* add the first delim */
  dest[0] = *(p + 1);
  /* check if there's another possible delim */
  if (p[2] == '|' && p[3] != '%' && p[3] != '\0') {
    dest[1] = *(p + 3);
    return 1;
  }
  return 0;
}