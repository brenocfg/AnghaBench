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
 int /*<<< orphan*/  B ; 
 unsigned int bbs_next_random_byte (int /*<<< orphan*/ *) ; 
 unsigned int* buffer ; 
 size_t qleft ; 
 size_t qsize ; 
 scalar_t__ qtotal ; 

int random_get_hex_bytes (char *s, int size) {
  static char hcyf[16] = "0123456789abcdef";
  int r = 0;
  while (qtotal > 0 && r < size) {
    unsigned c = buffer[qleft];
    buffer[qleft] = 0;
    *s++ = hcyf[c >> 4];
    *s++ = hcyf[c & 15];
    if (++qleft == qsize) {
      qleft = 0;
    }
    r += 2;
    qtotal--;
  }
  int t = 0;
  while (r < size && t < 65536) {
    unsigned c = bbs_next_random_byte (&B);
    *s++ = hcyf[c >> 4];
    *s++ = hcyf[c & 15];
    r += 2;
    t++;
  }

  if (r > size) {
    r = size;
  }

  return r;
}