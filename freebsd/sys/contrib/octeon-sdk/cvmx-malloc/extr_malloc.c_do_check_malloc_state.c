#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  TYPE_2__* mchunkptr ;
typedef  TYPE_2__* mbinptr ;
struct TYPE_23__ {struct TYPE_23__* bk; struct TYPE_23__* fd; } ;
struct TYPE_22__ {scalar_t__ top; int max_fast; scalar_t__ max_system_mem; scalar_t__ system_mem; TYPE_2__** fastbins; } ;
typedef  unsigned long INTERNAL_SIZE_T ;

/* Variables and functions */
 scalar_t__ FIRST_SORTED_BIN_SIZE ; 
 int MALLOC_ALIGNMENT ; 
 int /*<<< orphan*/  MAX_FAST_SIZE ; 
 unsigned long MINSIZE ; 
 int NBINS ; 
 int NFASTBINS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* bin_at (TYPE_1__*,int) ; 
 unsigned int bin_index (unsigned long) ; 
 int /*<<< orphan*/  check_chunk (TYPE_1__*,TYPE_2__*) ; 
 unsigned long chunksize (TYPE_2__*) ; 
 int /*<<< orphan*/  do_check_free_chunk (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  do_check_inuse_chunk (TYPE_1__*,TYPE_2__*) ; 
 int fastbin_index (unsigned long) ; 
 unsigned int get_binmap (TYPE_1__*,int) ; 
 int have_fastchunks (TYPE_1__*) ; 
 scalar_t__ initial_top (TYPE_1__*) ; 
 scalar_t__ inuse (TYPE_2__*) ; 
 TYPE_2__* last (TYPE_2__*) ; 
 TYPE_2__* next_chunk (TYPE_2__*) ; 
 int request2size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_check_malloc_state(mstate av)
{
  int i;
  mchunkptr p;
  mchunkptr q;
  mbinptr b;
  unsigned int binbit;
  int empty;
  unsigned int idx;
  INTERNAL_SIZE_T size;
  unsigned long total = 0;
  int max_fast_bin;

  /* internal size_t must be no wider than pointer type */
  assert(sizeof(INTERNAL_SIZE_T) <= sizeof(char*));

  /* alignment is a power of 2 */
  assert((MALLOC_ALIGNMENT & (MALLOC_ALIGNMENT-1)) == 0);

  /* cannot run remaining checks until fully initialized */
  if (av->top == 0 || av->top == initial_top(av))
    return;


  /* properties of fastbins */

  /* max_fast is in allowed range */
  assert((av->max_fast & ~1) <= request2size(MAX_FAST_SIZE));

  max_fast_bin = fastbin_index(av->max_fast);

  for (i = 0; i < NFASTBINS; ++i) {
    p = av->fastbins[i];

    /* all bins past max_fast are empty */
    if (i > max_fast_bin)
      assert(p == 0);

    while (p != 0) {
      /* each chunk claims to be inuse */
      do_check_inuse_chunk(av, p);
      total += chunksize(p);
      /* chunk belongs in this bin */
      assert(fastbin_index(chunksize(p)) == i);
      p = p->fd;
    }
  }

  if (total != 0)
    assert(have_fastchunks(av));
  else if (!have_fastchunks(av))
    assert(total == 0);

  /* check normal bins */
  for (i = 1; i < NBINS; ++i) {
    b = bin_at(av,i);

    /* binmap is accurate (except for bin 1 == unsorted_chunks) */
    if (i >= 2) {
      binbit = get_binmap(av,i);
      empty = last(b) == b;
      if (!binbit)
        assert(empty);
      else if (!empty)
        assert(binbit);
    }

    for (p = last(b); p != b; p = p->bk) {
      /* each chunk claims to be free */
      do_check_free_chunk(av, p);
      size = chunksize(p);
      total += size;
      if (i >= 2) {
        /* chunk belongs in bin */
        idx = bin_index(size);
        assert(idx == (unsigned int)i);
        /* lists are sorted */
        if ((unsigned long) size >= (unsigned long)(FIRST_SORTED_BIN_SIZE)) {
	  assert(p->bk == b ||
		 (unsigned long)chunksize(p->bk) >=
		 (unsigned long)chunksize(p));
	}
      }
      /* chunk is followed by a legal chain of inuse chunks */
      for (q = next_chunk(p);
           (q != av->top && inuse(q) &&
             (unsigned long)(chunksize(q)) >= MINSIZE);
           q = next_chunk(q))
        do_check_inuse_chunk(av, q);
    }
  }

  /* top chunk is OK */
  check_chunk(av, av->top);

  /* sanity checks for statistics */


  assert((unsigned long)(av->system_mem) <=
         (unsigned long)(av->max_system_mem));


}