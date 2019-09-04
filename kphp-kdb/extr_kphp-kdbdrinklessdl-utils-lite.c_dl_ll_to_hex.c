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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,long long) ; 

const char *dl_ll_to_hex (long long x) {
  static char tmp[50];
  snprintf (tmp, sizeof (tmp), "%llx", x);
  return tmp;
}