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
 int /*<<< orphan*/  feed_byte (char,int*) ; 

__attribute__((used)) static inline void copy_adjust_text (char *ptr, char *text, int text_len) {
  int state = 5;

  char *text_end = text + text_len;

  while (text < text_end) {
    feed_byte (*text, &state);
    if (!*text || (state == 2 && (unsigned char) *text < ' ' && *text != 9)) {
      *ptr++ = ' ';
    } else {
      *ptr++ = *text;
    }
    text++;
  }

  *ptr = 0;
}