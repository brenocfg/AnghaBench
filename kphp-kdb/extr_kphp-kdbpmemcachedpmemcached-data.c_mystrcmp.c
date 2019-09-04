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
 int memcmp (char const*,char const*,int) ; 

int mystrcmp (const char *str1, int l1, const char *str2, int l2) {
  int t = l1;
  if (l1 > l2) {
    t = l2;
  }
  t = memcmp (str1, str2, t);
  if (t != 0) {
    return t;
  }
  if (l1 < l2) {
    return -1;
  }
  if (l2 < l1) {
    return 1;
  }
  return 0;
}