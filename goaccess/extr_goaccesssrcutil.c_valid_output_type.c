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
 scalar_t__ strcmp (char*,char const*) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

int
valid_output_type (const char *filename)
{
  const char *ext = NULL;
  size_t sl;

  if ((ext = strrchr (filename, '.')) == NULL)
    return -1;

  ext++;
  /* Is extension 3<=len<=4? */
  sl = strlen (ext);
  if (sl < 3 || sl > 4)
    return 0;

  if (strcmp ("html", ext) == 0)
    return 1;

  if (strcmp ("json", ext) == 0)
    return 1;

  if (strcmp ("csv", ext) == 0)
    return 1;

  return 0;
}