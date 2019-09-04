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
struct TYPE_2__ {int output_format_idx; char const** output_formats; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char* strrchr (char const*,char) ; 
 char* xstrdup (char const*) ; 

int
find_output_type (char **filename, const char *ext, int alloc)
{
  int i;
  const char *dot = NULL;

  for (i = 0; i < conf.output_format_idx; ++i) {
    /* for backwards compatibility. i.e., -o json  */
    if (strcmp (conf.output_formats[i], ext) == 0)
      return 0;

    if ((dot = strrchr (conf.output_formats[i], '.')) != NULL &&
        strcmp (dot + 1, ext) == 0) {
      if (alloc)
        *filename = xstrdup (conf.output_formats[i]);
      return 0;
    }
  }

  return 1;
}