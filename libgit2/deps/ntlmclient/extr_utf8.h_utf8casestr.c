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
typedef  scalar_t__ utf8_int32_t ;

/* Variables and functions */
 void* utf8_null ; 
 void* utf8codepoint (void const*,scalar_t__*) ; 
 scalar_t__ utf8lwrcodepoint (scalar_t__) ; 

void *utf8casestr(const void *haystack, const void *needle) {
  const void *h = haystack;

  // if needle has no utf8 codepoints before the null terminating
  // byte then return haystack
  if ('\0' == *((const char *)needle)) {
    return (void *)haystack;
  }

  for (;;) {
    const void *maybeMatch = h;
    const void *n = needle;
    utf8_int32_t h_cp, n_cp;

    h = utf8codepoint(h, &h_cp);
    n = utf8codepoint(n, &n_cp);

    while ((0 != h_cp) && (0 != n_cp)) {
      h_cp = utf8lwrcodepoint(h_cp);
      n_cp = utf8lwrcodepoint(n_cp);

      // if we find a mismatch, bail out!
      if (h_cp != n_cp) {
        break;
      }

      h = utf8codepoint(h, &h_cp);
      n = utf8codepoint(n, &n_cp);
    }

    if (0 == n_cp) {
      // we found the whole utf8 string for needle in haystack at
      // maybeMatch, so return it
      return (void *)maybeMatch;
    }

    if (0 == h_cp) {
      // no match
      return utf8_null;
    }
  }
}