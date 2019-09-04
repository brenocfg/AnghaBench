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
 int /*<<< orphan*/  strncpy (char*,char const*,size_t const) ; 

void
xstrncpy (char *dest, const char *source, const size_t dest_size)
{
  strncpy (dest, source, dest_size);
  if (dest_size > 0) {
    dest[dest_size - 1] = '\0';
  } else {
    dest[0] = '\0';
  }
}