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
 void* utf8_null ; 

void *utf8valid(const void *str) {
  const char *s = (const char *)str;

  while ('\0' != *s) {
    if (0xf0 == (0xf8 & *s)) {
      // ensure each of the 3 following bytes in this 4-byte
      // utf8 codepoint began with 0b10xxxxxx
      if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2])) ||
          (0x80 != (0xc0 & s[3]))) {
        return (void *)s;
      }

      // ensure that our utf8 codepoint ended after 4 bytes
      if (0x80 == (0xc0 & s[4])) {
        return (void *)s;
      }

      // ensure that the top 5 bits of this 4-byte utf8
      // codepoint were not 0, as then we could have used
      // one of the smaller encodings
      if ((0 == (0x07 & s[0])) && (0 == (0x30 & s[1]))) {
        return (void *)s;
      }

      // 4-byte utf8 code point (began with 0b11110xxx)
      s += 4;
    } else if (0xe0 == (0xf0 & *s)) {
      // ensure each of the 2 following bytes in this 3-byte
      // utf8 codepoint began with 0b10xxxxxx
      if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2]))) {
        return (void *)s;
      }

      // ensure that our utf8 codepoint ended after 3 bytes
      if (0x80 == (0xc0 & s[3])) {
        return (void *)s;
      }

      // ensure that the top 5 bits of this 3-byte utf8
      // codepoint were not 0, as then we could have used
      // one of the smaller encodings
      if ((0 == (0x0f & s[0])) && (0 == (0x20 & s[1]))) {
        return (void *)s;
      }

      // 3-byte utf8 code point (began with 0b1110xxxx)
      s += 3;
    } else if (0xc0 == (0xe0 & *s)) {
      // ensure the 1 following byte in this 2-byte
      // utf8 codepoint began with 0b10xxxxxx
      if (0x80 != (0xc0 & s[1])) {
        return (void *)s;
      }

      // ensure that our utf8 codepoint ended after 2 bytes
      if (0x80 == (0xc0 & s[2])) {
        return (void *)s;
      }

      // ensure that the top 4 bits of this 2-byte utf8
      // codepoint were not 0, as then we could have used
      // one of the smaller encodings
      if (0 == (0x1e & s[0])) {
        return (void *)s;
      }

      // 2-byte utf8 code point (began with 0b110xxxxx)
      s += 2;
    } else if (0x00 == (0x80 & *s)) {
      // 1-byte ascii (began with 0b0xxxxxxx)
      s += 1;
    } else {
      // we have an invalid 0b1xxxxxxx utf8 code point entry
      return (void *)s;
    }
  }

  return utf8_null;
}