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
 char* _PATH_DEV ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
clean_ttyname (char *tty)
{
  char *res = tty;

  if (strncmp (res, _PATH_DEV, strlen(_PATH_DEV)) == 0)
    res += strlen(_PATH_DEV);
  if (strncmp (res, "pty/", 4) == 0)
    res += 4;
  if (strncmp (res, "ptym/", 5) == 0)
    res += 5;
  return res;
}