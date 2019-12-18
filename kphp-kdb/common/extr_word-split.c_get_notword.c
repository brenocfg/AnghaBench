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
 int get_notword_utf8 (char const*) ; 
 int* is_letter ; 
 int sigil_word_detect (int,char const*) ; 
 scalar_t__ word_split_utf8 ; 

int get_notword (const char *str) {
  if (word_split_utf8) {
    return get_notword_utf8 (str);
  }
  int b = 0, d = 0;
  int c;
  while (b <= 30 && d <= 4) {
    c = (unsigned char) *str;
    if (!c || (is_letter[c] & 0x3f)) {
      break;
    }
    if ((is_letter[c] & 0x40)) { /* && b removed see (http://vk.com/tasks?act=viewbug&bid=15344) */ 
      int z = sigil_word_detect (c, str + 1);
      if (z > 0 && z < 127) {
        break;
      }
    }
    if (c == '<' && str[1] == 'b') {
      if (!str[2]) {
	// str[0] = str[1] = ' ';
	return -1;
      } else if (str[2] == 'r') {
	if (str[3] == '>') {
	  str += 4;
	  b += 4;
	  d++;
	  continue;
	} else if (str[3] == '/' && str[4] == '>') {
	  str += 5;
	  b += 5;
	  d++;
	  continue;
	}
      }
    } else if (c == '&') {
      if (str[1] == '#') {
	int x, v = 0;
	for (x = 2; x <= 7 && str[x] <= '9' && str[x] >= '0'; x++) {
	  v *= 10;
	  v += str[x] - '0';
	}
	if (str[x] == ';' && v && v < 4096) {
	  x++;
          if (v < 128 && (is_letter[v] & 0x40) && b) {
            int z = sigil_word_detect (c, str + x);
            if (z >= 0 && z < 127) {
              break;
            }
          }
      	  if (v >= 0xc0 && v <= 0xff && v != 0xd7 && v != 0xf7) {
      	    break;
      	  }
	  b += x;
	  str += x;
	  d++;
	  continue;
	}
      } else {
	int x;
	for (x = 1; x <= 10 && str[x] >= 'a' && str[x] <= 'z'; x++) ;
	if (x > 1 && str[x] == ';') {
	  x++;
	  b += x;
	  str += x;
	  d++;
	  continue;
	}
      }
    }
    str++;
    b++;
    d++;
  }
  return b;
}