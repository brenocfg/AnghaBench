#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  int /*<<< orphan*/  mchunkptr ;
typedef  int /*<<< orphan*/  Void_t ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ATFORK_ARENA_PTR ; 
 int /*<<< orphan*/  _int_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* arena_for_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arena_key ; 
 scalar_t__ chunk_is_mmapped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem2chunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  munmap_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_getspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_atfork(Void_t* mem, const Void_t *caller)
{
  Void_t *vptr = NULL;
  mstate ar_ptr;
  mchunkptr p;                          /* chunk corresponding to mem */

  if (mem == 0)                              /* free(0) has no effect */
    return;

  p = mem2chunk(mem);         /* do not bother to replicate free_check here */

#if HAVE_MMAP
  if (chunk_is_mmapped(p))                       /* release mmapped memory. */
  {
    munmap_chunk(p);
    return;
  }
#endif

  ar_ptr = arena_for_chunk(p);
  tsd_getspecific(arena_key, vptr);
  if(vptr != ATFORK_ARENA_PTR)
    (void)mutex_lock(&ar_ptr->mutex);
  _int_free(ar_ptr, mem);
  if(vptr != ATFORK_ARENA_PTR)
    (void)mutex_unlock(&ar_ptr->mutex);
}