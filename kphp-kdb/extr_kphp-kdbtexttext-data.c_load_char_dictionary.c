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
struct char_dictionary {int dict_size; int* code_len; int max_bits; unsigned long long* first_codes; int** code_ptr; int* chars; int used_codes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct char_dictionary* load_index_part (struct char_dictionary*,long long,int,int /*<<< orphan*/ ) ; 

struct char_dictionary *load_char_dictionary (struct char_dictionary *D, long long offset) {
  int i, j, k;
  unsigned long long x;
  D = load_index_part (D, offset, 4+256, 0);
  if (!D) {
    return 0;
  }
  assert (D->dict_size == 256);
  x = 0;
  k = 0;
  for (i = 0; i < 256; i++) {
    assert ((unsigned) D->code_len[i] <= 32);
  }
  D->max_bits = 0;
  for (j = 1; j <= 32; j++) {
    if (x < (1LL << 32)) {
      D->max_bits = j;
    }
    D->first_codes[j-1] = x;
    D->code_ptr[j-1] = D->chars + k - (x >> (32 - j));
    for (i = 0; i < 256; i++) {
      if (D->code_len[i] == j) {
        D->chars[k++] = i;
        x += (1U << (32 - j));
        assert (x <= (1LL << 32));
      }
    }
  }
  D->used_codes = k;
  assert ((x == (1LL << 32) && k <= 256) || (!x && !k));
  return D;        
}