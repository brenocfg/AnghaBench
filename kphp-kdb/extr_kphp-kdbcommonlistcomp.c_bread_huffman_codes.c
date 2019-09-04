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
 scalar_t__ decode_cur_bit ; 
 int /*<<< orphan*/  decode_load_bit () ; 

void bread_huffman_codes (struct bitreader *br, int *l, int N, int *alphabet_size) {
  int i, m = br->m;
  *alphabet_size = 0;
  for (i = 0; i < N; i++) {
    int d = 0;
    if (decode_cur_bit) { d++; }
    decode_load_bit();
    d <<= 1;
    if (decode_cur_bit) { d++; }
    decode_load_bit();
    d <<= 1;
    if (decode_cur_bit) { d++; }
    decode_load_bit();
    d <<= 1;
    if (decode_cur_bit) { d++; }
    decode_load_bit();
    if (d) {
      (*alphabet_size)++;
    }
    l[i] = d;
  }
  br->m = m;
}