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
typedef  int Flag ;

/* Variables and functions */

__attribute__((used)) static Flag decBiStr(const char *targ, const char *str1, const char *str2) {
  for (;;targ++, str1++, str2++) {
    if (*targ!=*str1 && *targ!=*str2) return 0;
    // *targ has a match in one (or both, if terminator)
    if (*targ=='\0') break;
    } // forever
  return 1;
  }