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
 int strlen (char*) ; 

__attribute__((used)) static int rstrip (char *s, char ch) {
  int l = strlen (s), r = 0;
  while (l > 0 && s[l-1] == ch) {
    s[--l] = 0;
    r++;
  }
  return r;
}