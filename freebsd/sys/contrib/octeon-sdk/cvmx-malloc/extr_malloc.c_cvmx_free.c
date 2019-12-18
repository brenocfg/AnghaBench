#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mstate ;
typedef  int /*<<< orphan*/  mchunkptr ;
typedef  int /*<<< orphan*/  Void_t ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  stat_lock_wait; int /*<<< orphan*/  stat_lock_direct; } ;

/* Variables and functions */
 int /*<<< orphan*/  _int_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* arena_for_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  debug_printf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem2chunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void
public_fREe(Void_t* mem)
{
  mstate ar_ptr;
  mchunkptr p;                          /* chunk corresponding to mem */

  debug_printf("cvmx_free(%p)\n", mem);


  if (mem == 0)                              /* free(0) has no effect */
    return;

  p = mem2chunk(mem);


  ar_ptr = arena_for_chunk(p);
  assert(ar_ptr);
#if THREAD_STATS
  if(!mutex_trylock(&ar_ptr->mutex))
    ++(ar_ptr->stat_lock_direct);
  else {
    (void)mutex_lock(&ar_ptr->mutex);
    ++(ar_ptr->stat_lock_wait);
  }
#else
  (void)mutex_lock(&ar_ptr->mutex);
#endif
  _int_free(ar_ptr, mem);
  (void)mutex_unlock(&ar_ptr->mutex);
}