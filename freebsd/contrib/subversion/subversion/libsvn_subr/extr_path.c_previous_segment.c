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
typedef  size_t apr_size_t ;

/* Variables and functions */

__attribute__((used)) static apr_size_t
previous_segment(const char *path,
                 apr_size_t len)
{
  if (len == 0)
    return 0;

  while (len > 0 && path[--len] != '/')
    ;

  if (len == 0 && path[0] == '/')
    return 1;
  else
    return len;
}