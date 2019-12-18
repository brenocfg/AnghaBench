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

void *utf8str(const void *haystack, const void *needle) {
  const char *h = (const char *)haystack;

  // if needle has no utf8 codepoints before the null terminating
  // byte then return haystack
  if ('\0' == *((const char *)needle)) {
    return (void *)haystack;
  }

  while ('\0' != *h) {
    const char *maybeMatch = h;
    const char *n = (const char *)needle;

    while (*h == *n && (*h != '\0' && *n != '\0')) {
      n++;
      h++;
    }

    if ('\0' == *n) {
      // we found the whole utf8 string for needle in haystack at
      // maybeMatch, so return it
      return (void *)maybeMatch;
    } else {
      // h could be in the middle of an unmatching utf8 codepoint,
      // so we need to march it on to the next character beginning,
      if ('\0' != *h) {
        do {
          h++;
        } while (0x80 == (0xc0 & *h));
      }
    }
  }

  // no match
  return utf8_null;
}