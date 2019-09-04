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
 int HUFFMAN_MAX_CODE_LENGTH ; 
 scalar_t__ decode_cur_bit ; 
 int /*<<< orphan*/  decode_load_bit () ; 

int bread_huffman_decode_int (struct bitreader *br, int *firstcode ,int *symbols) {
  int m = br->m, l, v = 0;
  if (decode_cur_bit) {
    v++;
  }
  decode_load_bit();
  l = 1;
  while (v < firstcode[l]) {
    v <<= 1;
    if (decode_cur_bit) {
      v++;
    }
    decode_load_bit();
    l++;
  }
  br->m = m;
  return symbols[(HUFFMAN_MAX_CODE_LENGTH + 1) * (v - firstcode[l]) + l];
}