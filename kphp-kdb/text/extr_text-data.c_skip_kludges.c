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
 scalar_t__ feed_byte (char,int*) ; 

__attribute__((used)) static inline char *skip_kludges (char *text, int len) {
  char *ptr = text, *text_end = text + len, *kptr = text;
  int state = 5;

  while (ptr < text_end) {
    if (feed_byte (*ptr, &state)) {
      return ptr;
    }
    if (!*ptr || (state == 2 && (unsigned char) *ptr < 32 && *ptr != 9)) {
      return 0;
    }
    ++ptr;
  }

  if (state != 2) {
    kptr = ptr;
  }

  return kptr;
}