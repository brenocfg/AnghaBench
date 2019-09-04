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

__attribute__((used)) static inline int get_char_utf8 (unsigned int *x, const char *s) {
#define CHECK(condition) if (!(condition)) {*x = 0xFFFFFFFF; return -1;}
  int a = (unsigned char)s[0];
  if ((a & 0x80) == 0) {
    *x = a;
    return (a != 0);
  }

  CHECK ((a & 0x40) != 0);

  int b = (unsigned char)s[1];
  CHECK((b & 0xc0) == 0x80);
  if ((a & 0x20) == 0) {
    CHECK((a & 0x1e) > 0);
    *x = (((a & 0x1f) << 6) | (b & 0x3f));
    return 2;
  }

  int c = (unsigned char)s[2];
  CHECK((c & 0xc0) == 0x80);
  if ((a & 0x10) == 0) {
    CHECK(((a & 0x0f) | (b & 0x20)) > 0);
    *x = (((a & 0x0f) << 12) | ((b & 0x3f) << 6) | (c & 0x3f));
    return 3;
  }

  int d = (unsigned char)s[3];
  CHECK((d & 0xc0) == 0x80);
  if ((a & 0x08) == 0) {
    CHECK(((a & 0x07) | (b & 0x30)) > 0);
    *x = (((a & 0x07) << 18) | ((b & 0x3f) << 12) | ((c & 0x3f) << 6) | (d & 0x3f));
    return 4;
  }
  
  int e = (unsigned char)s[4];
  CHECK((e & 0xc0) == 0x80);
  if ((a & 0x04) == 0) {
    CHECK(((a & 0x03) | (b & 0x38)) > 0);
    *x = (((a & 0x03) << 24) | ((b & 0x3f) << 18) | ((c & 0x3f) << 12) | ((d & 0x3f) << 6) | (e & 0x3f));
    return 5;
  }
  
  int f = (unsigned char)s[5];
  CHECK((f & 0xc0) == 0x80);
  if ((a & 0x02) == 0) {
    CHECK(((a & 0x01) | (b & 0x3c)) > 0);
    *x = (((a & 0x01) << 30) | ((b & 0x3f) << 24) | ((c & 0x3f) << 18) | ((d & 0x3f) << 12) | ((e & 0x3f) << 6) | (f & 0x3f));
    return 6;
  }

  CHECK(0);
#undef CHECK
}