#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tchunkptr ;
typedef  TYPE_1__* mstate ;
typedef  int /*<<< orphan*/  mchunkptr ;
typedef  int /*<<< orphan*/  binmap_t ;
typedef  int /*<<< orphan*/  bindex_t ;
struct TYPE_10__ {int /*<<< orphan*/  treemap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORRUPTION_ERROR_ACTION (TYPE_1__*) ; 
 size_t MIN_CHUNK_SIZE ; 
 scalar_t__ RTCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* chunk2mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_plus_offset (int /*<<< orphan*/ ,size_t) ; 
 size_t chunksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_bit2idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  least_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leftmost_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_address (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_dv (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_inuse_and_pinuse (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_size_and_pinuse_of_free_chunk (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_size_and_pinuse_of_inuse_chunk (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * treebin_at (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_large_chunk (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void* tmalloc_small(mstate m, size_t nb) {
  tchunkptr t, v;
  size_t rsize;
  bindex_t i;
  binmap_t leastbit = least_bit(m->treemap);
  compute_bit2idx(leastbit, i);
  v = t = *treebin_at(m, i);
  rsize = chunksize(t) - nb;

  while ((t = leftmost_child(t)) != 0) {
    size_t trem = chunksize(t) - nb;
    if (trem < rsize) {
      rsize = trem;
      v = t;
    }
  }

  if (RTCHECK(ok_address(m, v))) {
    mchunkptr r = chunk_plus_offset(v, nb);
    assert(chunksize(v) == rsize + nb);
    if (RTCHECK(ok_next(v, r))) {
      unlink_large_chunk(m, v);
      if (rsize < MIN_CHUNK_SIZE)
	set_inuse_and_pinuse(m, v, (rsize + nb));
      else {
	set_size_and_pinuse_of_inuse_chunk(m, v, nb);
	set_size_and_pinuse_of_free_chunk(r, rsize);
	replace_dv(m, r, rsize);
      }
      return chunk2mem(v);
    }
  }

  CORRUPTION_ERROR_ACTION(m);
  return 0;
}