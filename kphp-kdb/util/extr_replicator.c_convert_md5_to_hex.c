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
typedef  int* md5_hash_t ;

/* Variables and functions */

__attribute__((used)) static void convert_md5_to_hex (char *output, md5_hash_t hash) {
  static char hcyf[16] = "0123456789abcdef";
  int i;
  for (i = 0; i < 16; i++) {
    output[2*i] = hcyf[(hash[i] >> 4) & 15];
    output[2*i+1] = hcyf[hash[i] & 15];
  }
  output[32] = 0;
}