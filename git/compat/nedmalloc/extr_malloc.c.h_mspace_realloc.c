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
typedef  int /*<<< orphan*/  mstate ;
typedef  int /*<<< orphan*/  mspace ;
typedef  int /*<<< orphan*/  mchunkptr ;

/* Variables and functions */
 int /*<<< orphan*/  USAGE_ERROR_ACTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mstate_for (int /*<<< orphan*/ ) ; 
 void* internal_realloc (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  mem2chunk (void*) ; 
 int /*<<< orphan*/  mspace_free (int /*<<< orphan*/ ,void*) ; 
 void* mspace_malloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ok_magic (int /*<<< orphan*/ ) ; 

void* mspace_realloc(mspace msp, void* oldmem, size_t bytes) {
  if (oldmem == 0)
    return mspace_malloc(msp, bytes);
#ifdef REALLOC_ZERO_BYTES_FREES
  if (bytes == 0) {
    mspace_free(msp, oldmem);
    return 0;
  }
#endif /* REALLOC_ZERO_BYTES_FREES */
  else {
#if FOOTERS
    mchunkptr p  = mem2chunk(oldmem);
    mstate ms = get_mstate_for(p);
#else /* FOOTERS */
    mstate ms = (mstate)msp;
#endif /* FOOTERS */
    if (!ok_magic(ms)) {
      USAGE_ERROR_ACTION(ms,ms);
      return 0;
    }
    return internal_realloc(ms, oldmem, bytes);
  }
}