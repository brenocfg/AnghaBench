#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  TYPE_2__* mchunkptr ;
struct TYPE_17__ {int granularity; } ;
struct TYPE_16__ {size_t prev_foot; size_t head; } ;
struct TYPE_15__ {char* least_addr; size_t footprint; size_t max_footprint; } ;
struct TYPE_14__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 scalar_t__ CALL_MREMAP (char*,size_t,size_t,int) ; 
 scalar_t__ CHUNK_ALIGN_MASK ; 
 size_t CINUSE_BIT ; 
 char* CMFAIL ; 
 int /*<<< orphan*/  FENCEPOST_HEAD ; 
 size_t IS_MMAPPED_BIT ; 
 size_t MMAP_FOOT_PAD ; 
 scalar_t__ SIX_SIZE_T_SIZES ; 
 size_t SIZE_T_SIZE ; 
 int /*<<< orphan*/  check_mmapped_chunk (TYPE_1__*,TYPE_2__*) ; 
 TYPE_10__* chunk_plus_offset (TYPE_2__*,size_t) ; 
 size_t chunksize (TYPE_2__*) ; 
 scalar_t__ is_small (size_t) ; 
 int /*<<< orphan*/  mark_inuse_foot (TYPE_1__*,TYPE_2__*,size_t) ; 
 size_t mmap_align (scalar_t__) ; 
 TYPE_3__ mparams ; 

__attribute__((used)) static mchunkptr mmap_resize(mstate m, mchunkptr oldp, size_t nb) {
  size_t oldsize = chunksize(oldp);
  if (is_small(nb)) /* Can't shrink mmap regions below small size */
    return 0;
  /* Keep old chunk if big enough but not too big */
  if (oldsize >= nb + SIZE_T_SIZE &&
      (oldsize - nb) <= (mparams.granularity << 1))
    return oldp;
  else {
    size_t offset = oldp->prev_foot & ~IS_MMAPPED_BIT;
    size_t oldmmsize = oldsize + offset + MMAP_FOOT_PAD;
    size_t newmmsize = mmap_align(nb + SIX_SIZE_T_SIZES + CHUNK_ALIGN_MASK);
    char* cp = (char*)CALL_MREMAP((char*)oldp - offset,
				  oldmmsize, newmmsize, 1);
    if (cp != CMFAIL) {
      mchunkptr newp = (mchunkptr)(cp + offset);
      size_t psize = newmmsize - offset - MMAP_FOOT_PAD;
      newp->head = (psize|CINUSE_BIT);
      mark_inuse_foot(m, newp, psize);
      chunk_plus_offset(newp, psize)->head = FENCEPOST_HEAD;
      chunk_plus_offset(newp, psize+SIZE_T_SIZE)->head = 0;

      if (cp < m->least_addr)
	m->least_addr = cp;
      if ((m->footprint += newmmsize - oldmmsize) > m->max_footprint)
	m->max_footprint = m->footprint;
      check_mmapped_chunk(m, newp);
      return newp;
    }
  }
  return 0;
}