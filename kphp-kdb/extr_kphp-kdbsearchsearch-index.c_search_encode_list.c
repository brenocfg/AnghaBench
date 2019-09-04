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
struct search_index_word {int len; int len_subseq; scalar_t__ bytes_subseq; scalar_t__ bytes; } ;
typedef  int /*<<< orphan*/  pair_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ in_title (int /*<<< orphan*/ *) ; 
 scalar_t__ search_encode_core (int /*<<< orphan*/ *,int,int,struct search_index_word*,int,int const,int) ; 

__attribute__((used)) static int search_encode_list (pair_t *P, int len, struct search_index_word *W, const int compression_methods[2], int quiet) {
  W->len = len;
  //W->requests = (len >= 0xffff0 ? 0xffff : (len >> 4) + 1);

  W->bytes = W->bytes_subseq = 0;
  assert (len > 0);

  int len_sub = 0;
  while (len > 0) {
    len--;
    if (in_title (P)) {
      len_sub++;
    }
    P++;
  }

  len = W->len;
  P-=len;
  W->len_subseq = len_sub;
  int res = 0;
  res += search_encode_core (P, len, len, W, 0, compression_methods[0], quiet);
  res += search_encode_core (P, len, len_sub, W, 1, compression_methods[1], quiet);
  return res;
}