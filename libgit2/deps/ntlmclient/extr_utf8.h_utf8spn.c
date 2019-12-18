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

size_t utf8spn(const void *src, const void *accept) {
  const char *s = (const char *)src;
  size_t chars = 0;

  while ('\0' != *s) {
    const char *a = (const char *)accept;
    size_t offset = 0;

    while ('\0' != *a) {
      // checking that if *r is the start of a utf8 codepoint
      // (it is not 0b10xxxxxx) and we have successfully matched
      // a previous character (0 < offset) - we found a match
      if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
        // found a match, so increment the number of utf8 codepoints
        // that have matched and stop checking whether any other utf8
        // codepoints in a match
        chars++;
        s += offset;
        break;
      } else {
        if (*a == s[offset]) {
          offset++;
          a++;
        } else {
          // a could be in the middle of an unmatching utf8 codepoint,
          // so we need to march it on to the next character beginning,
          do {
            a++;
          } while (0x80 == (0xc0 & *a));

          // reset offset too as we found a mismatch
          offset = 0;
        }
      }
    }

    // if a got to its terminating null byte, then we didn't find a match.
    // Return the current number of matched utf8 codepoints
    if ('\0' == *a) {
      return chars;
    }
  }

  return chars;
}