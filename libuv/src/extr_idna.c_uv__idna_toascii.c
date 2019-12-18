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
 int uv__idna_toascii_label (char const*,char const*,char**,char*) ; 
 unsigned int uv__utf8_decode1 (char const**,char const*) ; 

long uv__idna_toascii(const char* s, const char* se, char* d, char* de) {
  const char* si;
  const char* st;
  unsigned c;
  char* ds;
  int rc;

  ds = d;

  for (si = s; si < se; /* empty */) {
    st = si;
    c = uv__utf8_decode1(&si, se);

    if (c != '.')
      if (c != 0x3002)  /* 。 */
        if (c != 0xFF0E)  /* ． */
          if (c != 0xFF61)  /* ｡ */
            continue;

    rc = uv__idna_toascii_label(s, st, &d, de);

    if (rc < 0)
      return rc;

    if (d < de)
      *d++ = '.';

    s = si;
  }

  if (s < se) {
    rc = uv__idna_toascii_label(s, se, &d, de);

    if (rc < 0)
      return rc;
  }

  if (d < de)
    *d++ = '\0';

  return d - ds;  /* Number of bytes written. */
}