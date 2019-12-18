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
struct list_decoder {int p; int M; int last; int /*<<< orphan*/ * decode_int; scalar_t__ data; struct bitreader br; } ;

/* Variables and functions */
 scalar_t__ HUFFMAN_MAX_CODE_LENGTH ; 
 int /*<<< orphan*/  bread_huffman_codes (struct bitreader*,int*,int,int*) ; 
 int /*<<< orphan*/  canonical_huffman (int*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  llrun_decode_int ; 
 int /*<<< orphan*/  llrun_decode_int_single_bucket ; 

__attribute__((used)) static void llrun_decoder_init (struct list_decoder *dec) {
  struct bitreader *br = &dec->br;
  int l[32], i, alphabet_size;
  bread_huffman_codes (br, l, dec->p, &alphabet_size);
  if (alphabet_size <= 1) {
    /* only one symbol in alphabet */
    for (i = 0; i < dec->p; i++) {
      if (l[i]) {
        dec->M = i;
        break;
      }
    }
    dec->decode_int = &llrun_decode_int_single_bucket;
  } else {
    dec->M = -1;
    canonical_huffman (l, dec->p, HUFFMAN_MAX_CODE_LENGTH, dec->data, NULL, dec->data + (HUFFMAN_MAX_CODE_LENGTH + 1));
    dec->decode_int = &llrun_decode_int;
  }
  dec->last = -1;
}