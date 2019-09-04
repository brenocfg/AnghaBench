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
 int get_word (char const*) ; 
 unsigned char* is_letter ; 
 unsigned char* is_letter_utf8 ; 
 scalar_t__ word_split_utf8 ; 

int std_sigil_word_detect (int sigil, const char *str) {
  if (sigil == 0x1f) {
    int z = 0;
    while (z < 32 && str[z] < 0) {
      z++;
    }
    return (str[z] & 0x40) ? z + 1 : -1;
  }
  unsigned char *letter = word_split_utf8 ? is_letter_utf8 : is_letter;
  if (letter['.'] & 8) {
    return -1;
  }
  if (sigil != '[') {
    if (sigil != '#') {
      letter['.'] ^= 8;
      letter['-'] ^= 8;
    }
    int z = get_word (str);
    if (sigil != '#') {
      letter['.'] ^= 8;
      letter['-'] ^= 8;
    }
    return z > 0 ? z : -1;
  }
  if (*str != '[') {
    return -1;
  }
  const char *tmp = str + 1;

  while (
         (tmp <= str + 120) &&
         (
          (*tmp >= '0' && *tmp <= '9') || 
          (*tmp >= 'A' && *tmp <= 'Z') ||
          (*tmp >= 'a' && *tmp <= 'z') || 
          (*tmp == '_') ||
          (*tmp == '-')
         )
        ) {
    ++tmp;
  }

  if (*tmp == ']' && tmp[1] == ']') {
    return tmp + 2 - str;
  }

  return -1;
}