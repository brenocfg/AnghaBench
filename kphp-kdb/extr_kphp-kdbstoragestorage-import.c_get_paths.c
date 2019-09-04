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
 int MAX_DIRS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int get_paths (const char *paths, char *P[MAX_DIRS]) {
  char *s = strdup (paths), *p;
  int n = 0;
  for (p = strtok (s, ":"); p != NULL; p = strtok (NULL, ":")) {
    if (n >= MAX_DIRS) {
      free (s);
      return -1;
    }
    P[n++] = p;
  }
  return n;
}