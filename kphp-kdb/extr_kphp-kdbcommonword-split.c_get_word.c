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
 int get_word_utf8 (char const*) ; 
 int* is_letter ; 
 int sigil_word_detect (int,char const*) ; 
 scalar_t__ word_split_utf8 ; 

int get_word (const char *str) {
  if (word_split_utf8) {
    return get_word_utf8 (str);
  }
  static int inside_star = 0;
  int b = 0, d = 0;
  int c = (unsigned char) *str;
  if (is_letter[c] & 0x40) {
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
    if (is_letter[c] & 8) {
      str++;
      if (++b == 127) {
	break;
      }
    } else if (is_letter[c] & 4) {
      if (d == (inside_star ? 30 : 4)) {
	break;
      }
      str++;
      d++;
      b++;
    } else if (c == '&') {
      if (str[1] == '#') {
	int x, v = 0;
	for (x = 2; x <= 7 && str[x] <= '9' && str[x] >= '0'; x++) {
	  v *= 10;
	  v += str[x] - '0';
	}
	if (str[x] == ';' && v && v < 4096) {
	  x++;
          if (!b && v < 128 && (is_letter[v] & 0x40)) {
            int z = sigil_word_detect (v, str + x);
            if (z >= 0 && z < 120) {
              return z + x;
            }
          }
      	  if (v >= 0xc0 && v <= 0xff && v != 0xd7 && v != 0xf7) {
      	    str += x;
      	    b += x;
      	    continue;
      	  }
	}
      }	
      break;
    } else {
      break;
    }
  }
  return b;
}