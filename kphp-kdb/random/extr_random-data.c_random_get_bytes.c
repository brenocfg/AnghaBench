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
 int /*<<< orphan*/  bbs_next_random_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * buffer ; 
 size_t qleft ; 
 size_t qsize ; 
 scalar_t__ qtotal ; 

int random_get_bytes (char *s, int size) {
  int r = 0;
  while (qtotal > 0 && r < size) {
    *s++ = buffer[qleft];
    buffer[qleft] = 0;
    if (++qleft == qsize) {
      qleft = 0;
    }
    r++;
    qtotal--;
  }
  int t = 0;
  while (r < size && t < 65536) {
    *s++ = bbs_next_random_byte (&B);
    r++;
    t++;
  }
  return r;
}