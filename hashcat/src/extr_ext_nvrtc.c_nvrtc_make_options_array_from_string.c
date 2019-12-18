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
 char* strtok_r (char*,char*,char**) ; 

int nvrtc_make_options_array_from_string (char *string, char **options)
{
  char *saveptr = NULL;

  char *next = strtok_r (string, " ", &saveptr);

  int cnt = 0;

  do
  {
    options[cnt] = next;

    cnt++;

  } while ((next = strtok_r ((char *) NULL, " ", &saveptr)) != NULL);

  return cnt;
}