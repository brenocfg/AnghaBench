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

__attribute__((used)) static unsigned uv__utf8_decode1_slow(const char** p,
                                      const char* pe,
                                      unsigned a) {
  unsigned b;
  unsigned c;
  unsigned d;
  unsigned min;

  if (a > 0xF7)
    return -1;

  switch (*p - pe) {
  default:
    if (a > 0xEF) {
      min = 0x10000;
      a = a & 7;
      b = (unsigned char) *(*p)++;
      c = (unsigned char) *(*p)++;
      d = (unsigned char) *(*p)++;
      break;
    }
    /* Fall through. */
  case 2:
    if (a > 0xDF) {
      min = 0x800;
      b = 0x80 | (a & 15);
      c = (unsigned char) *(*p)++;
      d = (unsigned char) *(*p)++;
      a = 0;
      break;
    }
    /* Fall through. */
  case 1:
    if (a > 0xBF) {
      min = 0x80;
      b = 0x80;
      c = 0x80 | (a & 31);
      d = (unsigned char) *(*p)++;
      a = 0;
      break;
    }
    return -1;  /* Invalid continuation byte. */
  }

  if (0x80 != (0xC0 & (b ^ c ^ d)))
    return -1;  /* Invalid sequence. */

  b &= 63;
  c &= 63;
  d &= 63;
  a = (a << 18) | (b << 12) | (c << 6) | d;

  if (a < min)
    return -1;  /* Overlong sequence. */

  if (a > 0x10FFFF)
    return -1;  /* Four-byte sequence > U+10FFFF. */

  if (a >= 0xD800 && a <= 0xDFFF)
    return -1;  /* Surrogate pair. */

  return a;
}