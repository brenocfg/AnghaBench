#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  scalar_t__ mchunkptr ;
typedef  int /*<<< orphan*/  Void_t ;
struct TYPE_8__ {scalar_t__ top; } ;
typedef  unsigned long INTERNAL_SIZE_T ;

/* Variables and functions */
 unsigned long MALLOC_ALIGN_MASK ; 
 int /*<<< orphan*/  MALLOC_COPY (unsigned long*,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  MALLOC_FAILURE_ACTION ; 
 unsigned long MINSIZE ; 
 unsigned long PREV_INUSE ; 
 unsigned long SIZE_SZ ; 
 int /*<<< orphan*/  _int_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _int_malloc (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_inuse_chunk (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  check_malloc_state (TYPE_1__*) ; 
 int /*<<< orphan*/  checked_request2size (size_t,unsigned long) ; 
 int /*<<< orphan*/ * chunk2mem (scalar_t__) ; 
 void* chunk_at_offset (scalar_t__,unsigned long) ; 
 unsigned long chunksize (scalar_t__) ; 
 int /*<<< orphan*/  inuse (scalar_t__) ; 
 scalar_t__ mem2chunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_arena_for_chunk (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  set_head (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  set_head_size (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  set_inuse_bit_at_offset (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  unlink (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static Void_t*
_int_realloc(mstate av, Void_t* oldmem, size_t bytes)
{
  INTERNAL_SIZE_T  nb;              /* padded request size */

  mchunkptr        oldp;            /* chunk corresponding to oldmem */
  INTERNAL_SIZE_T  oldsize;         /* its size */

  mchunkptr        newp;            /* chunk to return */
  INTERNAL_SIZE_T  newsize;         /* its size */
  Void_t*          newmem;          /* corresponding user mem */

  mchunkptr        next;            /* next contiguous chunk after oldp */

  mchunkptr        remainder;       /* extra space at end of newp */
  unsigned long    remainder_size;  /* its size */

  mchunkptr        bck;             /* misc temp for linking */
  mchunkptr        fwd;             /* misc temp for linking */

  unsigned long    copysize;        /* bytes to copy */
  unsigned int     ncopies;         /* INTERNAL_SIZE_T words to copy */
  INTERNAL_SIZE_T* s;               /* copy source */
  INTERNAL_SIZE_T* d;               /* copy destination */


#if REALLOC_ZERO_BYTES_FREES
  if (bytes == 0) {
    _int_free(av, oldmem);
    return 0;
  }
#endif

  /* realloc of null is supposed to be same as malloc */
  if (oldmem == 0) return _int_malloc(av, bytes);

  checked_request2size(bytes, nb);

  oldp    = mem2chunk(oldmem);
  oldsize = chunksize(oldp);

  check_inuse_chunk(av, oldp);

  // force to act like not mmapped
  if (1) {

    if ((unsigned long)(oldsize) >= (unsigned long)(nb)) {
      /* already big enough; split below */
      newp = oldp;
      newsize = oldsize;
    }

    else {
      next = chunk_at_offset(oldp, oldsize);

      /* Try to expand forward into top */
      if (next == av->top &&
          (unsigned long)(newsize = oldsize + chunksize(next)) >=
          (unsigned long)(nb + MINSIZE)) {
        set_head_size(oldp, nb );
        av->top = chunk_at_offset(oldp, nb);
        set_head(av->top, (newsize - nb) | PREV_INUSE);
    	check_inuse_chunk(av, oldp);
        set_arena_for_chunk(oldp, av);
        return chunk2mem(oldp);
      }

      /* Try to expand forward into next chunk;  split off remainder below */
      else if (next != av->top &&
               !inuse(next) &&
               (unsigned long)(newsize = oldsize + chunksize(next)) >=
               (unsigned long)(nb)) {
        newp = oldp;
        unlink(next, bck, fwd);
      }

      /* allocate, copy, free */
      else {
        newmem = _int_malloc(av, nb - MALLOC_ALIGN_MASK);
        if (newmem == 0)
          return 0; /* propagate failure */

        newp = mem2chunk(newmem);
        newsize = chunksize(newp);

        /*
          Avoid copy if newp is next chunk after oldp.
        */
        if (newp == next) {
          newsize += oldsize;
          newp = oldp;
        }
        else {
          /*
            Unroll copy of <= 36 bytes (72 if 8byte sizes)
            We know that contents have an odd number of
            INTERNAL_SIZE_T-sized words; minimally 3.
          */

          copysize = oldsize - SIZE_SZ;
          s = (INTERNAL_SIZE_T*)(oldmem);
          d = (INTERNAL_SIZE_T*)(newmem);
          ncopies = copysize / sizeof(INTERNAL_SIZE_T);
          assert(ncopies >= 3);

          if (ncopies > 9)
            MALLOC_COPY(d, s, copysize);

          else {
            *(d+0) = *(s+0);
            *(d+1) = *(s+1);
            *(d+2) = *(s+2);
            if (ncopies > 4) {
              *(d+3) = *(s+3);
              *(d+4) = *(s+4);
              if (ncopies > 6) {
                *(d+5) = *(s+5);
                *(d+6) = *(s+6);
                if (ncopies > 8) {
                  *(d+7) = *(s+7);
                  *(d+8) = *(s+8);
                }
              }
            }
          }

          _int_free(av, oldmem);
          set_arena_for_chunk(newp, av);
          check_inuse_chunk(av, newp);
          return chunk2mem(newp);
        }
      }
    }

    /* If possible, free extra space in old or extended chunk */

    assert((unsigned long)(newsize) >= (unsigned long)(nb));

    remainder_size = newsize - nb;

    if (remainder_size < MINSIZE) { /* not enough extra to split off */
      set_head_size(newp, newsize);
      set_inuse_bit_at_offset(newp, newsize);
    }
    else { /* split remainder */
      remainder = chunk_at_offset(newp, nb);
      set_head_size(newp, nb );
      set_head(remainder, remainder_size | PREV_INUSE );
      /* Mark remainder as inuse so free() won't complain */
      set_inuse_bit_at_offset(remainder, remainder_size);
      set_arena_for_chunk(remainder, av);
      _int_free(av, chunk2mem(remainder));
    }

    set_arena_for_chunk(newp, av);
    check_inuse_chunk(av, newp);
    return chunk2mem(newp);
  }

  /*
    Handle mmap cases
  */

  else {
    /* If !HAVE_MMAP, but chunk_is_mmapped, user must have overwritten mem */
    check_malloc_state(av);
    MALLOC_FAILURE_ACTION;
    return 0;
  }
}