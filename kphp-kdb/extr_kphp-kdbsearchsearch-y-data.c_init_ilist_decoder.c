#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int doc_id; TYPE_4__* sword; } ;
typedef  TYPE_1__ ilist_decoder_t ;
typedef  int /*<<< orphan*/  iheap_en_t ;
typedef  scalar_t__ hash_t ;
struct TYPE_6__ {scalar_t__ word; int /*<<< orphan*/  file_offset; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 TYPE_4__* IndexWords ; 
 int /*<<< orphan*/  idx_items ; 
 int idx_words ; 
 int /*<<< orphan*/  init_decoder (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  searchy_is_term (scalar_t__) ; 

int init_ilist_decoder (iheap_en_t *H, ilist_decoder_t *D, hash_t word) {
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
    return 0;
  }

  D->sword = IndexWords + a;
  init_decoder (H, D, idx_items, D->sword->len, &D->sword->file_offset, searchy_is_term (word));
  return 1;
}