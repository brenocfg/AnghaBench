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
 int memcmp (char*,char*,int) ; 

__attribute__((used)) static int cmp_str (char *a, int la, char *b, int lb) {
  if (la < lb) {
    if (!la) { return -1; }
    return (memcmp (a, b, la) <= 0) ? -1 : 1;
  }
  if (la > lb) {
    if (!lb) { return 1; }
    return (memcmp (a, b, lb) >= 0) ? 1 : -1;
  }
  if (!la) {
    return 0;
  }
  return memcmp (a, b, la);
}