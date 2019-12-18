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
 int Q_order ; 
 scalar_t__ Q_slice_limit ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 

int targ_regenerate_search_extras (char *buffer) {
  char *ptr = buffer;
  *ptr++ = '#';
  if (Q_slice_limit > 0) {
    if (Q_order & 8) {
      if (Q_order & 4) {
        *ptr++ = 'R';
      } else {
        *ptr++ = 'r';
      }
    } else {
      if (Q_order & 4) {
        *ptr++ = 'I';
      } else {
        *ptr++ = 'i';
      }
    }
    ptr += sprintf (ptr, "%d", Q_slice_limit);
  }
  *ptr++ = '%';
  *ptr++ = ')';
  *ptr = 0;
  return ptr - buffer;
}