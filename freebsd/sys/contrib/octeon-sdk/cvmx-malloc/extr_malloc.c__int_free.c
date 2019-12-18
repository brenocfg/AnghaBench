#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  TYPE_2__* mfastbinptr ;
typedef  TYPE_2__* mchunkptr ;
typedef  int /*<<< orphan*/  Void_t ;
struct TYPE_30__ {scalar_t__ prev_size; struct TYPE_30__* bk; struct TYPE_30__* fd; } ;
struct TYPE_29__ {TYPE_2__* top; TYPE_2__** fastbins; scalar_t__ max_fast; } ;
typedef  scalar_t__ INTERNAL_SIZE_T ;

/* Variables and functions */
 unsigned long FASTBIN_CONSOLIDATION_THRESHOLD ; 
 scalar_t__ PREV_INUSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_chunk (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  check_free_chunk (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  check_inuse_chunk (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* chunk_at_offset (TYPE_2__*,long) ; 
 int /*<<< orphan*/  chunk_is_mmapped (TYPE_2__*) ; 
 scalar_t__ chunksize (TYPE_2__*) ; 
 int /*<<< orphan*/  clear_inuse_bit_at_offset (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t fastbin_index (scalar_t__) ; 
 scalar_t__ have_fastchunks (TYPE_1__*) ; 
 int inuse_bit_at_offset (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  malloc_consolidate (TYPE_1__*) ; 
 TYPE_2__* mem2chunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_inuse (TYPE_2__*) ; 
 int /*<<< orphan*/  set_fastchunks (TYPE_1__*) ; 
 int /*<<< orphan*/  set_foot (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  set_head (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  unlink (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* unsorted_chunks (TYPE_1__*) ; 

__attribute__((used)) static void
_int_free(mstate av, Void_t* mem)
{
  mchunkptr       p;           /* chunk corresponding to mem */
  INTERNAL_SIZE_T size;        /* its size */
  mfastbinptr*    fb;          /* associated fastbin */
  mchunkptr       nextchunk;   /* next contiguous chunk */
  INTERNAL_SIZE_T nextsize;    /* its size */
  int             nextinuse;   /* true if nextchunk is used */
  INTERNAL_SIZE_T prevsize;    /* size of previous contiguous chunk */
  mchunkptr       bck;         /* misc temp for linking */
  mchunkptr       fwd;         /* misc temp for linking */


  /* free(0) has no effect */
  if (mem != 0) {
    p = mem2chunk(mem);
    size = chunksize(p);

    check_inuse_chunk(av, p);

    /*
      If eligible, place chunk on a fastbin so it can be found
      and used quickly in malloc.
    */

    if ((unsigned long)(size) <= (unsigned long)(av->max_fast)

#if TRIM_FASTBINS
        /*
           If TRIM_FASTBINS set, don't place chunks
           bordering top into fastbins
        */
        && (chunk_at_offset(p, size) != av->top)
#endif
        ) {

      set_fastchunks(av);
      fb = &(av->fastbins[fastbin_index(size)]);
      p->fd = *fb;
      *fb = p;
    }

    /*
       Consolidate other non-mmapped chunks as they arrive.
    */

    else if (!chunk_is_mmapped(p)) {
      nextchunk = chunk_at_offset(p, size);
      nextsize = chunksize(nextchunk);
      assert(nextsize > 0);

      /* consolidate backward */
      if (!prev_inuse(p)) {
        prevsize = p->prev_size;
        size += prevsize;
        p = chunk_at_offset(p, -((long) prevsize));
        unlink(p, bck, fwd);
      }

      if (nextchunk != av->top) {
        /* get and clear inuse bit */
        nextinuse = inuse_bit_at_offset(nextchunk, nextsize);

        /* consolidate forward */
        if (!nextinuse) {
          unlink(nextchunk, bck, fwd);
          size += nextsize;
        } else
	  clear_inuse_bit_at_offset(nextchunk, 0);

        /*
          Place the chunk in unsorted chunk list. Chunks are
          not placed into regular bins until after they have
          been given one chance to be used in malloc.
        */

        bck = unsorted_chunks(av);
        fwd = bck->fd;
        p->bk = bck;
        p->fd = fwd;
        bck->fd = p;
        fwd->bk = p;

        set_head(p, size | PREV_INUSE);
        set_foot(p, size);

        check_free_chunk(av, p);
      }

      /*
         If the chunk borders the current high end of memory,
         consolidate into top
      */

      else {
        size += nextsize;
        set_head(p, size | PREV_INUSE);
        av->top = p;
        check_chunk(av, p);
      }

      /*
        If freeing a large space, consolidate possibly-surrounding
        chunks. Then, if the total unused topmost memory exceeds trim
        threshold, ask malloc_trim to reduce top.

        Unless max_fast is 0, we don't know if there are fastbins
        bordering top, so we cannot tell for sure whether threshold
        has been reached unless fastbins are consolidated.  But we
        don't want to consolidate on each free.  As a compromise,
        consolidation is performed if FASTBIN_CONSOLIDATION_THRESHOLD
        is reached.
      */

      if ((unsigned long)(size) >= FASTBIN_CONSOLIDATION_THRESHOLD) {
        if (have_fastchunks(av))
          malloc_consolidate(av);
      }
    }
  }
}