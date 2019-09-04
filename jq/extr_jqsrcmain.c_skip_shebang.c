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
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static const char *skip_shebang(const char *p) {
  if (strncmp(p, "#!", sizeof("#!") - 1) != 0)
    return p;
  const char *n = strchr(p, '\n');
  if (n == NULL || n[1] != '#')
    return p;
  n = strchr(n + 1, '\n');
  if (n == NULL || n[1] == '#' || n[1] == '\0' || n[-1] != '\\' || n[-2] == '\\')
    return p;
  n = strchr(n + 1, '\n');
  if (n == NULL)
    return p;
  return n+1;
}