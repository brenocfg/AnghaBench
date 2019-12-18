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
 char* skipspc (char*) ; 

__attribute__((used)) static char *getword (char **ptr, int *len) {
  char *start = skipspc (*ptr), *tmp = start;

  while (*tmp && *tmp != ' ' && *tmp != '\t' && *tmp != '\n') {
    ++tmp;
  }

  *ptr = tmp;
  *len = tmp - start;

  if (!*len) {
    return 0;
  }

  return start;
}