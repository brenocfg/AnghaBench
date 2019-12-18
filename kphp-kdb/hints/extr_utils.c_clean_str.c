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
 scalar_t__ MAX_NAME_SIZE ; 
 char* prep_buf ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

char *clean_str (char *x) {
  if (strlen (x) >= MAX_NAME_SIZE) {
    return x;
  }

  char *s = prep_buf;
  int skip;

  while (*x != 0) {
    skip = !strncmp (x, "amp+", 4) ||
           !strncmp (x, "gt+", 3) ||
           !strncmp (x, "lt+", 3) ||
           !strncmp (x, "quot+", 5) ||
           !strncmp (x, "ft+", 3) ||
           !strncmp (x, "feat+", 5) ||
           (((x[0] == '1' && x[1] == '9') || (x[0] == '2' && x[1] == '0')) && ('0' <= x[2] && x[2] <= '9') && ('0' <= x[3] && x[3] <= '9') && x[4] == '+') ||
           !strncmp (x, "092+", 4) ||
           !strncmp (x, "33+", 3) ||
           !strncmp (x, "34+", 3) ||
           !strncmp (x, "36+", 3) ||
           !strncmp (x, "39+", 3) ||
           !strncmp (x, "60+", 3) ||
           !strncmp (x, "62+", 3) ||
           !strncmp (x, "8232+", 5) ||
           !strncmp (x, "8233+", 5);
    do {
      *s = *x;
      if (!skip) {
        s++;
      }
    } while (*x++ != '+');
  }
  *s = 0;

  return prep_buf;
}