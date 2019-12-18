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

__attribute__((used)) static char *mask_ctx_parse_maskfile_find_mask (char *line_buf, const size_t line_len)
{
  char *mask_buf = line_buf;

  bool escaped = false;

  for (size_t i = 0; i < line_len; i++)
  {
    if (escaped == true)
    {
      escaped = false;
    }
    else
    {
      if (line_buf[i] == '\\')
      {
        escaped = true;
      }
      else if (line_buf[i] == ',')
      {
        mask_buf = line_buf + i + 1;
      }
    }
  }

  return mask_buf;
}