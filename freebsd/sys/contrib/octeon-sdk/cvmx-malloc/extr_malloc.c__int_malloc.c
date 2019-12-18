#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  TYPE_2__* mfastbinptr ;
typedef  TYPE_2__* mchunkptr ;
typedef  TYPE_2__* mbinptr ;
typedef  int /*<<< orphan*/  Void_t ;
struct TYPE_34__ {struct TYPE_34__* fd; struct TYPE_34__* bk; scalar_t__ size; } ;
struct TYPE_33__ {unsigned int* binmap; TYPE_2__* top; TYPE_2__* last_remainder; TYPE_2__** fastbins; scalar_t__ max_fast; } ;
typedef  unsigned long INTERNAL_SIZE_T ;

/* Variables and functions */
 unsigned int BINMAPSHIFT ; 
 unsigned int BINMAPSIZE ; 
 scalar_t__ FIRST_SORTED_BIN_SIZE ; 
 unsigned long MINSIZE ; 
 unsigned long PREV_INUSE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* bin_at (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  check_malloced_chunk (TYPE_1__*,TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  check_remalloced_chunk (TYPE_1__*,TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  checked_request2size (size_t,unsigned long) ; 
 int /*<<< orphan*/ * chunk2mem (TYPE_2__*) ; 
 TYPE_2__* chunk_at_offset (TYPE_2__*,unsigned long) ; 
 unsigned long chunksize (TYPE_2__*) ; 
 size_t fastbin_index (unsigned long) ; 
 scalar_t__ have_fastchunks (TYPE_1__*) ; 
 unsigned int idx2bit (unsigned int) ; 
 unsigned int idx2block (unsigned int) ; 
 int in_smallbin_range (unsigned long) ; 
 void* largebin_index (unsigned long) ; 
 TYPE_2__* last (TYPE_2__*) ; 
 int /*<<< orphan*/  malloc_consolidate (TYPE_1__*) ; 
 int /*<<< orphan*/  mark_bin (TYPE_1__*,int) ; 
 TYPE_2__* next_bin (TYPE_2__*) ; 
 int /*<<< orphan*/  set_arena_for_chunk (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_foot (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  set_head (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  set_inuse_bit_at_offset (TYPE_2__*,unsigned long) ; 
 void* smallbin_index (unsigned long) ; 
 int /*<<< orphan*/  unlink (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* unsorted_chunks (TYPE_1__*) ; 

__attribute__((used)) static Void_t*
_int_malloc(mstate av, size_t bytes)
{
  INTERNAL_SIZE_T nb;               /* normalized request size */
  unsigned int    idx;              /* associated bin index */
  mbinptr         bin;              /* associated bin */
  mfastbinptr*    fb;               /* associated fastbin */

  mchunkptr       victim;           /* inspected/selected chunk */
  INTERNAL_SIZE_T size;             /* its size */
  int             victim_index;     /* its bin index */

  mchunkptr       remainder;        /* remainder from a split */
  unsigned long   remainder_size;   /* its size */

  unsigned int    block;            /* bit map traverser */
  unsigned int    bit;              /* bit map traverser */
  unsigned int    map;              /* current word of binmap */

  mchunkptr       fwd;              /* misc temp for linking */
  mchunkptr       bck;              /* misc temp for linking */

  /*
    Convert request size to internal form by adding SIZE_SZ bytes
    overhead plus possibly more to obtain necessary alignment and/or
    to obtain a size of at least MINSIZE, the smallest allocatable
    size. Also, checked_request2size traps (returning 0) request sizes
    that are so large that they wrap around zero when padded and
    aligned.
  */


  checked_request2size(bytes, nb);

  /*
    If the size qualifies as a fastbin, first check corresponding bin.
    This code is safe to execute even if av is not yet initialized, so we
    can try it without checking, which saves some time on this fast path.
  */

  if ((unsigned long)(nb) <= (unsigned long)(av->max_fast)) {
    fb = &(av->fastbins[(fastbin_index(nb))]);
    if ( (victim = *fb) != 0) {
      *fb = victim->fd;
      check_remalloced_chunk(av, victim, nb);
      set_arena_for_chunk(victim, av);
      return chunk2mem(victim);
    }
  }

  /*
    If a small request, check regular bin.  Since these "smallbins"
    hold one size each, no searching within bins is necessary.
    (For a large request, we need to wait until unsorted chunks are
    processed to find best fit. But for small ones, fits are exact
    anyway, so we can check now, which is faster.)
  */

  if (in_smallbin_range(nb)) {
    idx = smallbin_index(nb);
    bin = bin_at(av,idx);

    if ( (victim = last(bin)) != bin) {
      if (victim == 0) /* initialization check */
        malloc_consolidate(av);
      else {
        bck = victim->bk;
        set_inuse_bit_at_offset(victim, nb);
        bin->bk = bck;
        bck->fd = bin;

        set_arena_for_chunk(victim, av);
        check_malloced_chunk(av, victim, nb);
        return chunk2mem(victim);
      }
    }
  }

  /*
     If this is a large request, consolidate fastbins before continuing.
     While it might look excessive to kill all fastbins before
     even seeing if there is space available, this avoids
     fragmentation problems normally associated with fastbins.
     Also, in practice, programs tend to have runs of either small or
     large requests, but less often mixtures, so consolidation is not
     invoked all that often in most programs. And the programs that
     it is called frequently in otherwise tend to fragment.
  */

  else {
    idx = largebin_index(nb);
    if (have_fastchunks(av))
      malloc_consolidate(av);
  }

  /*
    Process recently freed or remaindered chunks, taking one only if
    it is exact fit, or, if this a small request, the chunk is remainder from
    the most recent non-exact fit.  Place other traversed chunks in
    bins.  Note that this step is the only place in any routine where
    chunks are placed in bins.

    The outer loop here is needed because we might not realize until
    near the end of malloc that we should have consolidated, so must
    do so and retry. This happens at most once, and only when we would
    otherwise need to expand memory to service a "small" request.
  */

  for(;;) {

    while ( (victim = unsorted_chunks(av)->bk) != unsorted_chunks(av)) {
      bck = victim->bk;
      size = chunksize(victim);

      /*
         If a small request, try to use last remainder if it is the
         only chunk in unsorted bin.  This helps promote locality for
         runs of consecutive small requests. This is the only
         exception to best-fit, and applies only when there is
         no exact fit for a small chunk.
      */

      if (in_smallbin_range(nb) &&
          bck == unsorted_chunks(av) &&
          victim == av->last_remainder &&
          (unsigned long)(size) > (unsigned long)(nb + MINSIZE)) {

        /* split and reattach remainder */
        remainder_size = size - nb;
        remainder = chunk_at_offset(victim, nb);
        unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
        av->last_remainder = remainder;
        remainder->bk = remainder->fd = unsorted_chunks(av);

        set_head(victim, nb | PREV_INUSE);
        set_head(remainder, remainder_size | PREV_INUSE);
        set_foot(remainder, remainder_size);

        set_arena_for_chunk(victim, av);
        check_malloced_chunk(av, victim, nb);
        return chunk2mem(victim);
      }

      /* remove from unsorted list */
      unsorted_chunks(av)->bk = bck;
      bck->fd = unsorted_chunks(av);

      /* Take now instead of binning if exact fit */

      if (size == nb) {
        set_inuse_bit_at_offset(victim, size);
        set_arena_for_chunk(victim, av);
        check_malloced_chunk(av, victim, nb);
        return chunk2mem(victim);
      }

      /* place chunk in bin */

      if (in_smallbin_range(size)) {
        victim_index = smallbin_index(size);
        bck = bin_at(av, victim_index);
        fwd = bck->fd;
      }
      else {
        victim_index = largebin_index(size);
        bck = bin_at(av, victim_index);
        fwd = bck->fd;

        if (fwd != bck) {
          /* if smaller than smallest, place first */
          if ((unsigned long)(size) < (unsigned long)(bck->bk->size)) {
            fwd = bck;
            bck = bck->bk;
          }
          else if ((unsigned long)(size) >= 
                   (unsigned long)(FIRST_SORTED_BIN_SIZE)) {

            /* maintain large bins in sorted order */
            size |= PREV_INUSE; /* Or with inuse bit to speed comparisons */
            while ((unsigned long)(size) < (unsigned long)(fwd->size)) {
              fwd = fwd->fd;
	    }
            bck = fwd->bk;
          }
        }
      }

      mark_bin(av, victim_index);
      victim->bk = bck;
      victim->fd = fwd;
      fwd->bk = victim;
      bck->fd = victim;
    }

    /*
      If a large request, scan through the chunks of current bin in
      sorted order to find smallest that fits.  This is the only step
      where an unbounded number of chunks might be scanned without doing
      anything useful with them. However the lists tend to be short.
    */

    if (!in_smallbin_range(nb)) {
      bin = bin_at(av, idx);

      for (victim = last(bin); victim != bin; victim = victim->bk) {
	size = chunksize(victim);

	if ((unsigned long)(size) >= (unsigned long)(nb)) {
	  remainder_size = size - nb;
	  unlink(victim, bck, fwd);

	  /* Exhaust */
	  if (remainder_size < MINSIZE)  {
	    set_inuse_bit_at_offset(victim, size);
        set_arena_for_chunk(victim, av);
	    check_malloced_chunk(av, victim, nb);
	    return chunk2mem(victim);
	  }
	  /* Split */
	  else {
	    remainder = chunk_at_offset(victim, nb);
	    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
	    remainder->bk = remainder->fd = unsorted_chunks(av);
	    set_head(victim, nb | PREV_INUSE);
	    set_head(remainder, remainder_size | PREV_INUSE);
	    set_foot(remainder, remainder_size);
        set_arena_for_chunk(victim, av);
	    check_malloced_chunk(av, victim, nb);
	    return chunk2mem(victim);
	  }
	}
      }
    }

    /*
      Search for a chunk by scanning bins, starting with next largest
      bin. This search is strictly by best-fit; i.e., the smallest
      (with ties going to approximately the least recently used) chunk
      that fits is selected.

      The bitmap avoids needing to check that most blocks are nonempty.
      The particular case of skipping all bins during warm-up phases
      when no chunks have been returned yet is faster than it might look.
    */

    ++idx;
    bin = bin_at(av,idx);
    block = idx2block(idx);
    map = av->binmap[block];
    bit = idx2bit(idx);

    for (;;) {

      /* Skip rest of block if there are no more set bits in this block.  */
      if (bit > map || bit == 0) {
        do {
          if (++block >= BINMAPSIZE)  /* out of bins */
            goto use_top;
        } while ( (map = av->binmap[block]) == 0);

        bin = bin_at(av, (block << BINMAPSHIFT));
        bit = 1;
      }

      /* Advance to bin with set bit. There must be one. */
      while ((bit & map) == 0) {
        bin = next_bin(bin);
        bit <<= 1;
        assert(bit != 0);
      }

      /* Inspect the bin. It is likely to be non-empty */
      victim = last(bin);

      /*  If a false alarm (empty bin), clear the bit. */
      if (victim == bin) {
        av->binmap[block] = map &= ~bit; /* Write through */
        bin = next_bin(bin);
        bit <<= 1;
      }

      else {
        size = chunksize(victim);

        /*  We know the first chunk in this bin is big enough to use. */
        assert((unsigned long)(size) >= (unsigned long)(nb));

        remainder_size = size - nb;

        /* unlink */
        bck = victim->bk;
        bin->bk = bck;
        bck->fd = bin;

        /* Exhaust */
        if (remainder_size < MINSIZE) {
          set_inuse_bit_at_offset(victim, size);
          set_arena_for_chunk(victim, av);
          check_malloced_chunk(av, victim, nb);
          return chunk2mem(victim);
        }

        /* Split */
        else {
          remainder = chunk_at_offset(victim, nb);

          unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
          remainder->bk = remainder->fd = unsorted_chunks(av);
          /* advertise as last remainder */
          if (in_smallbin_range(nb))
            av->last_remainder = remainder;

          set_head(victim, nb | PREV_INUSE);
          set_head(remainder, remainder_size | PREV_INUSE);
          set_foot(remainder, remainder_size);
          set_arena_for_chunk(victim, av);
          check_malloced_chunk(av, victim, nb);
          return chunk2mem(victim);
        }
      }
    }

  use_top:
    /*
      If large enough, split off the chunk bordering the end of memory
      (held in av->top). Note that this is in accord with the best-fit
      search rule.  In effect, av->top is treated as larger (and thus
      less well fitting) than any other available chunk since it can
      be extended to be as large as necessary (up to system
      limitations).

      We require that av->top always exists (i.e., has size >=
      MINSIZE) after initialization, so if it would otherwise be
      exhuasted by current request, it is replenished. (The main
      reason for ensuring it exists is that we may need MINSIZE space
      to put in fenceposts in sysmalloc.)
    */

    victim = av->top;
    size = chunksize(victim);

    if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE)) {
      remainder_size = size - nb;
      remainder = chunk_at_offset(victim, nb);
      av->top = remainder;
      set_head(victim, nb | PREV_INUSE);
      set_head(remainder, remainder_size | PREV_INUSE);

      set_arena_for_chunk(victim, av);
      check_malloced_chunk(av, victim, nb);
      return chunk2mem(victim);
    }

    /*
      If there is space available in fastbins, consolidate and retry,
      to possibly avoid expanding memory. This can occur only if nb is
      in smallbin range so we didn't consolidate upon entry.
    */

    else if (have_fastchunks(av)) {
      assert(in_smallbin_range(nb));
      malloc_consolidate(av);
      idx = smallbin_index(nb); /* restore original bin index */
    }

    /*
       Otherwise, relay to handle system-dependent cases
    */
    else
      return(NULL); // sysmalloc not supported
  }
}