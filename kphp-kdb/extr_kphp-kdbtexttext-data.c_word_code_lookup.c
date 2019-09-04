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
struct word_dictionary {int max_bits; unsigned int* first_codes; struct file_word_dictionary_entry*** code_ptr; } ;
struct file_word_dictionary_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline struct file_word_dictionary_entry *word_code_lookup (struct word_dictionary *D, unsigned code, int *l) {
  int a = -1, b = D->max_bits, c;
  while (b - a > 1) {
    c = ((a + b) >> 1);
    if (D->first_codes[c] <= code) { a = c; } else { b = c; }
  }
  assert (a >= 0);
  *l = a + 1;
  return D->code_ptr[a][code >> (31 - a)];
}