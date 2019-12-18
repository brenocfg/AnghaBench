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
struct bitreader {int m; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ decode_cur_bit ; 
 int /*<<< orphan*/  decode_load_bit () ; 

unsigned long long bread_nbitsull (struct bitreader *br, int n) {
  assert (!(n & -64));
  unsigned long long d = 0;
  int m = br->m;
  while (n--) {
    d <<= 1;
    if (decode_cur_bit) {
      d++;
    }
    decode_load_bit();
  }
  br->m = m;
  return d;
}