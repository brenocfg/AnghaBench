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
 unsigned int bread_nbits (struct bitreader*,int) ; 
 scalar_t__ decode_cur_bit ; 
 int /*<<< orphan*/  decode_load_bit () ; 

unsigned int bread_gamma_code (struct bitreader *br) {
  int k = 0, m = br->m;
  while (decode_cur_bit) {
    k++;
    decode_load_bit();
  }
  decode_load_bit();
  br->m = m;
  return (1U << k) | bread_nbits (br, k);
}