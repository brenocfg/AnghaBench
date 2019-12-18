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
 char* utf8_null ; 

void *utf8rchr(const void *src, int chr) {
  const char *s = (const char *)src;
  const char *match = utf8_null;
  char c[5] = {'\0', '\0', '\0', '\0', '\0'};

  if (0 == chr) {
    // being asked to return position of null terminating byte, so
    // just run s to the end, and return!
    while ('\0' != *s) {
      s++;
    }
    return (void *)s;
  } else if (0 == ((int)0xffffff80 & chr)) {
    // 1-byte/7-bit ascii
    // (0b0xxxxxxx)
    c[0] = (char)chr;
  } else if (0 == ((int)0xfffff800 & chr)) {
    // 2-byte/11-bit utf8 code point
    // (0b110xxxxx 0b10xxxxxx)
    c[0] = 0xc0 | (char)(chr >> 6);
    c[1] = 0x80 | (char)(chr & 0x3f);
  } else if (0 == ((int)0xffff0000 & chr)) {
    // 3-byte/16-bit utf8 code point
    // (0b1110xxxx 0b10xxxxxx 0b10xxxxxx)
    c[0] = 0xe0 | (char)(chr >> 12);
    c[1] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[2] = 0x80 | (char)(chr & 0x3f);
  } else { // if (0 == ((int)0xffe00000 & chr)) {
    // 4-byte/21-bit utf8 code point
    // (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx)
    c[0] = 0xf0 | (char)(chr >> 18);
    c[1] = 0x80 | (char)((chr >> 12) & 0x3f);
    c[2] = 0x80 | (char)((chr >> 6) & 0x3f);
    c[3] = 0x80 | (char)(chr & 0x3f);
  }

  // we've created a 2 utf8 codepoint string in c that is
  // the utf8 character asked for by chr, and a null
  // terminating byte

  while ('\0' != *s) {
    size_t offset = 0;

    while (s[offset] == c[offset]) {
      offset++;
    }

    if ('\0' == c[offset]) {
      // we found a matching utf8 code point
      match = s;
      s += offset;
    } else {
      s += offset;

      // need to march s along to next utf8 codepoint start
      // (the next byte that doesn't match 0b10xxxxxx)
      if ('\0' != *s) {
        do {
          s++;
        } while (0x80 == (0xc0 & *s));
      }
    }
  }

  // return the last match we found (or 0 if no match was found)
  return (void *)match;
}