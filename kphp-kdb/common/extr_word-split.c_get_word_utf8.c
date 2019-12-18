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
 int* is_letter_utf8 ; 
 int sigil_word_detect (int,char const*) ; 

int get_word_utf8 (const char *str) {
  static int inside_star = 0;
  int b = 0, d = 0;
  int c = (unsigned char) *str;
  if (is_letter_utf8[c] & 0x40) {
    if (c == '*') {
      inside_star = 1;
    }
    int z = sigil_word_detect (c, str + 1);
    if (c == '*') {
      inside_star = 0;
    }
    if (z >= 0 && z < 127) {
      return z + 1;
    }
  }
  while (b <= 120) {
    c = (unsigned char) *str;
    if (c >= 0xc2 && c <= 0xdf && (signed char) str[1] < -0x40) {
      c = ((c & 0x1f) << 6) | (str[1] & 0x3f);
      if (is_letter_utf8[c] & 8) {
	str += 2;
	b += 2;
	if (b >= 126) {
	  break;
	}
      } else {
	break;
      }
    } else if (is_letter_utf8[c] & 8) {
      str++;
      if (++b == 126) {
	break;
      }
    } else if (is_letter_utf8[c] & 4) {
      if (d == (inside_star ? 30 : 4)) {
	break;
      }
      str++;
      d++;
      b++;
      break;
    } else {
      break;
    }
  }
  return b;
}