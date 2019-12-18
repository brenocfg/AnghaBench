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

size_t utf8cspn(const void *src, const void *reject) {
  const char *s = (const char *)src;
  size_t chars = 0;

  while ('\0' != *s) {
    const char *r = (const char *)reject;
    size_t offset = 0;

    while ('\0' != *r) {
      // checking that if *r is the start of a utf8 codepoint
      // (it is not 0b10xxxxxx) and we have successfully matched
      // a previous character (0 < offset) - we found a match
      if ((0x80 != (0xc0 & *r)) && (0 < offset)) {
        return chars;
      } else {
        if (*r == s[offset]) {
          // part of a utf8 codepoint matched, so move our checking
          // onwards to the next byte
          offset++;
          r++;
        } else {
          // r could be in the middle of an unmatching utf8 code point,
          // so we need to march it on to the next character beginning,

          do {
            r++;
          } while (0x80 == (0xc0 & *r));

          // reset offset too as we found a mismatch
          offset = 0;
        }
      }
    }

    // the current utf8 codepoint in src did not match reject, but src
    // could have been partway through a utf8 codepoint, so we need to
    // march it onto the next utf8 codepoint starting byte
    do {
      s++;
    } while ((0x80 == (0xc0 & *s)));
    chars++;
  }

  return chars;
}