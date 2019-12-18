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
 scalar_t__ isalpha (char) ; 
 scalar_t__ rl_filename_completion_desired ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *
printable_part (char *pathname)
{
  char *temp;

  temp = rl_filename_completion_desired ? strrchr (pathname, '/') : (char *)NULL;
#if defined (__MSDOS__)
  if (rl_filename_completion_desired && temp == 0 && isalpha (pathname[0]) && pathname[1] == ':')
    temp = pathname + 1;
#endif
  return (temp ? ++temp : pathname);
}