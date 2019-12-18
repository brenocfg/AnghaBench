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
 scalar_t__ strcmp (char const*,char const*) ; 

int
str_inarray (const char *s, const char *arr[], int size)
{
  int i;
  for (i = 0; i < size; i++) {
    if (strcmp (arr[i], s) == 0)
      return i;
  }
  return -1;
}