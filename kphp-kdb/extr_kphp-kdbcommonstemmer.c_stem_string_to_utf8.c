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

int stem_string_to_utf8 (const unsigned char *s, int *v) {
  int n = 0;
#define CHECK(x) if (!(x)) {v[n] = 0; return n;}

  int a, b, c, d;

  while (1) {
    a = *s++;
    CHECK(a != 0) ;
    if ((a & 0x80) == 0) {
      v[n++] = a;
    } else if ((a & 0x40) == 0) {
      CHECK(0);
    } else if ((a & 0x20) == 0) {
      b = *s++;
      CHECK((b & 0xc0) == 0x80);
      v[n++] = ((a & 0x1f) << 6) | (b & 0x3f);
    } else if ((a & 0x10) == 0) {
      b = *s++;
      CHECK((b & 0xc0) == 0x80);
      c = *s++;
      CHECK((c & 0xc0) == 0x80);
      v[n++] = ((a & 0x0f) << 12) | ((b & 0x3f) << 6) | (c & 0x3f);
    } else if ((a & 0x08) == 0) {
      b = *s++;
      CHECK((b & 0xc0) == 0x80);
      c = *s++;
      CHECK((c & 0xc0) == 0x80);
      d = *s++;
      CHECK((d & 0xc0) == 0x80);
      v[n++] = ((a & 0x07) << 18) | ((b & 0x3f) << 12) | ((c & 0x3f) << 6) | (d & 0x3f);
    } else {
      CHECK(0);
    }
  }
}