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
struct bitreader {int dummy; } ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int bread_gamma_code (struct bitreader*) ; 
 int bread_get_bits_read (struct bitreader*) ; 
 int /*<<< orphan*/  bread_init (struct bitreader*,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* idx_word_lookup (int /*<<< orphan*/ ,int*) ; 

int get_idx_word_list_len (hash_t word) {
  int len;
  unsigned char *ptr = idx_word_lookup (word, &len);
  if (!ptr) {
    return 0;
  }
  struct bitreader br;
  bread_init (&br, ptr, 0);
  int x = bread_gamma_code (&br);
  assert (bread_get_bits_read (&br) <= len * 8);
  return x;
}