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
 scalar_t__ TRUE ; 
 char** parts ; 
 scalar_t__ pn ; 
 scalar_t__ separator (char) ; 

__attribute__((used)) static void split (char *s) {
  pn = 0;
  while (TRUE) {
    int end = 0;
    while (!end && *s && separator (*s)) {
      if (*s == '\t') {
        end = 1;
      }
      *s++ = 0;
    }
    if (!*s) {
      break;
    }
    parts[pn++] = s;
    while (*s && !separator (*s)) {
      s++;
    }
  }
}