#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct list_encoder {int /*<<< orphan*/  bw; int /*<<< orphan*/  (* encode_int ) (struct list_encoder*,int) ;} ;
struct TYPE_5__ {int doc_id; TYPE_3__* sword; int /*<<< orphan*/  dec; int /*<<< orphan*/  extra; } ;
typedef  TYPE_1__ ilist_decoder_t ;
typedef  scalar_t__ hash_t ;
struct TYPE_7__ {scalar_t__ word; unsigned int doc_id_and_priority; } ;
struct TYPE_6__ {scalar_t__ word; int /*<<< orphan*/  file_offset; int /*<<< orphan*/  bytes; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 TYPE_4__* IndexHapaxLegomena ; 
 TYPE_3__* IndexWords ; 
 int /*<<< orphan*/  bwrite_gamma_code (int /*<<< orphan*/ *,unsigned int) ; 
 int idx_hapax_legomena ; 
 int /*<<< orphan*/  idx_items ; 
 int idx_words ; 
 int /*<<< orphan*/  init_decoder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le_golomb ; 
 int /*<<< orphan*/  list_encoder_finish (struct list_encoder*) ; 
 int /*<<< orphan*/  list_encoder_init (struct list_encoder*,int /*<<< orphan*/ ,int,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct list_encoder*,int) ; 

int init_ilist_decoder (ilist_decoder_t *D, hash_t word) {
  /* *D is already cleared,
     since D is a part of already cleared heap entry
  */
  D->doc_id = -1;

  int a = -1, b = idx_words, c;

  while (b - a > 1) {
    c = ((a + b) >> 1);
    if (IndexWords[c].word <= word) { a = c; } else { b = c; }
  }

  if (a < 0 || IndexWords[a].word != word) {
    a = -1;
    b = idx_hapax_legomena;
    while (b - a > 1) {
      c = ((a + b) >> 1);
      if (IndexHapaxLegomena[c].word <= word) { a = c; } else { b = c; }
    }
    if (a >= 0 && IndexHapaxLegomena[a].word == word) {
      unsigned int u = IndexHapaxLegomena[a].doc_id_and_priority;
      int doc_id = u & 0x7fffffff;
      unsigned freq1, freq2;
      if (u & 0x80000000) {
        //hapax legomena in title
        freq1 = 2;
        freq2 = 1;
      } else {
        //hapax legomena in text
        freq1 = 1;
        freq2 = 1;
      }
      void *Li = &D->extra, *Le = Li + 8;

      struct list_encoder enc;
      list_encoder_init (&enc, idx_items, 1, Li, Le, le_golomb, 0);
      enc.encode_int (&enc, doc_id);
      bwrite_gamma_code (&enc.bw, freq1);
      bwrite_gamma_code (&enc.bw, freq2);
      list_encoder_finish (&enc);
      return 1;
    }
    return 0;
  }
  D->sword = IndexWords + a;
  init_decoder (&D->dec, idx_items, D->sword->len, D->sword->bytes, &D->sword->file_offset);
  return 1;
}