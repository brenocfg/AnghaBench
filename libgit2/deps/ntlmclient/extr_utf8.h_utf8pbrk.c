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

void *utf8pbrk(const void *str, const void *accept) {
  const char *s = (const char *)str;

  while ('\0' != *s) {
    const char *a = (const char *)accept;
    size_t offset = 0;

    while ('\0' != *a) {
      // checking that if *a is the start of a utf8 codepoint
      // (it is not 0b10xxxxxx) and we have successfully matched
      // a previous character (0 < offset) - we found a match
      if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
        return (void *)s;
      } else {
        if (*a == s[offset]) {
          // part of a utf8 codepoint matched, so move our checking
          // onwards to the next byte
          offset++;
          a++;
        } else {
          // r could be in the middle of an unmatching utf8 code point,
          // so we need to march it on to the next character beginning,

          do {
            a++;
          } while (0x80 == (0xc0 & *a));

          // reset offset too as we found a mismatch
          offset = 0;
        }
      }
    }

    // we found a match on the last utf8 codepoint
    if (0 < offset) {
      return (void *)s;
    }

    // the current utf8 codepoint in src did not match accept, but src
    // could have been partway through a utf8 codepoint, so we need to
    // march it onto the next utf8 codepoint starting byte
    do {
      s++;
    } while ((0x80 == (0xc0 & *s)));
  }

  return utf8_null;
}