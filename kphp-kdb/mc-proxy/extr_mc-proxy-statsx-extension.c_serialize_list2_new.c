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
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *serialize_list2_new (char *ptr, const char *name, int *list, int num) {
  if (!*list) {
    return ptr;
  }
  ptr += sprintf (ptr, "s:%ld:\"%s\";a:%d:{", (long) strlen (name), name, *list);
  int i;
  for (i = 0; i < 2 * (*list); i++) {
    ptr += sprintf (ptr, "i:%d;", list[i + 1]);
  }
  *ptr++ = '}';
  return ptr;
}