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
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 

int
subset_compare (char *string_to_compare, char *template_string)
{
  int match;
  if (template_string != (char *) NULL && string_to_compare != (char *) NULL
      && strlen (string_to_compare) <= strlen (template_string))
    match =
      (strncmp
       (template_string, string_to_compare, strlen (string_to_compare)) == 0);
  else
    match = 0;
  return match;
}