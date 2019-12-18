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
typedef  int /*<<< orphan*/  GColors ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  locate_attr_color (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 
 char* strpbrk (char*,char*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int
parse_attr_color (GColors * color, const char *value)
{
  char *line, *ptr, *start;
  int ret = 0;

  line = xstrdup (value);

  start = strchr (line, ' ');
  if ((!start) || (!*(start + 1))) {
    LOG_DEBUG (("attempted to parse color attr: %s\n", value));
    goto clean;
  }

  start++;
  while (1) {
    if ((ptr = strpbrk (start, ", ")) != NULL)
      *ptr = 0;
    locate_attr_color (color, start);
    if (ptr == NULL)
      break;
    start = ptr + 1;
  }

clean:
  free (line);

  return ret;
}