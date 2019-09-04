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

void string_to_utf8 (const unsigned char *s, int *v) {
  int *tv = v;
#define CHECK(x) if (!(x)) {v = tv; break;}

  int a, b, c, d;

  while (*s) {
    a = *s++;
    if ((a & 0x80) == 0) {
      *v++ = a;
    } else if ((a & 0x40) == 0) {
      CHECK(0);
    } else if ((a & 0x20) == 0) {
      b = *s++;
      CHECK((b & 0xc0) == 0x80);
      CHECK((a & 0x1e) > 0);
      *v++ = ((a & 0x1f) << 6) | (b & 0x3f);
    } else if ((a & 0x10) == 0) {
      b = *s++;
      CHECK((b & 0xc0) == 0x80);
      c = *s++;
      CHECK((c & 0xc0) == 0x80);
      CHECK(((a & 0x0f) | (b & 0x20)) > 0);
      *v++ = ((a & 0x0f) << 12) | ((b & 0x3f) << 6) | (c & 0x3f);
    } else if ((a & 0x08) == 0) {
      b = *s++;
      CHECK((b & 0xc0) == 0x80);
      c = *s++;
      CHECK((c & 0xc0) == 0x80);
      d = *s++;
      CHECK((d & 0xc0) == 0x80);
      CHECK(((a & 0x07) | (b & 0x30)) > 0);
      *v++ = ((a & 0x07) << 18) | ((b & 0x3f) << 12) | ((c & 0x3f) << 6) | (d & 0x3f);
    } else {
      CHECK(0);
    }
  }
  *v = 0;
#undef CHECK
}