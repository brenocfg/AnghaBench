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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  parse_color (char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void
parse_colors (const char *colors[], size_t n)
{
  char *line;
  size_t i;

  for (i = 0; i < n; ++i) {
    line = strdup (colors[i]);
    /* did not find a valid format */
    if (strchr (line, ':') == NULL) {
      free (line);
      continue;
    }
    parse_color (line);
  }
}