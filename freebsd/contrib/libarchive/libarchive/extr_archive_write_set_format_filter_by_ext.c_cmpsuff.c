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
 int strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static 
int cmpsuff(const char *str, const char *suffix)
{
  size_t length_str, length_suffix;

  if ((str == NULL) || (suffix == NULL))
    return -1;

  length_str = strlen(str);
  length_suffix = strlen(suffix);

  if (length_str >= length_suffix) {
    return strcmp(str + (length_str - length_suffix), suffix);
  } else {
    return -1;
  }
}