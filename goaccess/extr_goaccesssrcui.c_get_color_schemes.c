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
struct TYPE_2__ {int /*<<< orphan*/  color_idx; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int COLORS ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 char** xmalloc (int) ; 

__attribute__((used)) static const char **
get_color_schemes (size_t * size)
{
  const char *choices[] = {
    "Monokai",
    "Monochrome",
    "Green",
    "Custom Scheme"
  };
  int i, j, n = ARRAY_SIZE (choices);
  const char **opts = xmalloc (sizeof (char *) * n);

  for (i = 0, j = 0; i < n; ++i) {
    if (!conf.color_idx && !strcmp ("Custom Scheme", choices[i]))
      continue;
    if (COLORS < 256 && !strcmp ("Monokai", choices[i]))
      continue;
    opts[j++] = choices[i];
  }
  *size = j;

  return opts;
}