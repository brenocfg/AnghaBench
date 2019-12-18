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
typedef  int /*<<< orphan*/  uv_loop_t ;

/* Variables and functions */
 int UV__LOOPS_CHUNK_SIZE ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** uv__loops ; 
 int uv__loops_capacity ; 
 int /*<<< orphan*/  uv__loops_lock ; 
 int uv__loops_size ; 
 int /*<<< orphan*/ ** uv__realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__loops_remove(uv_loop_t* loop) {
  int loop_index;
  int smaller_capacity;
  uv_loop_t** new_loops;

  uv_mutex_lock(&uv__loops_lock);

  for (loop_index = 0; loop_index < uv__loops_size; ++loop_index) {
    if (uv__loops[loop_index] == loop)
      break;
  }
  /* If loop was not found, ignore */
  if (loop_index == uv__loops_size)
    goto loop_removed;

  uv__loops[loop_index] = uv__loops[uv__loops_size - 1];
  uv__loops[uv__loops_size - 1] = NULL;
  --uv__loops_size;

  if (uv__loops_size == 0) {
    uv__loops_capacity = 0;
    uv__free(uv__loops);
    uv__loops = NULL;
    goto loop_removed;
  }

  /* If we didn't grow to big skip downsizing */
  if (uv__loops_capacity < 4 * UV__LOOPS_CHUNK_SIZE)
    goto loop_removed;

  /* Downsize only if more than half of buffer is free */
  smaller_capacity = uv__loops_capacity / 2;
  if (uv__loops_size >= smaller_capacity)
    goto loop_removed;
  new_loops = uv__realloc(uv__loops, sizeof(uv_loop_t*) * smaller_capacity);
  if (!new_loops)
    goto loop_removed;
  uv__loops = new_loops;
  uv__loops_capacity = smaller_capacity;

loop_removed:
  uv_mutex_unlock(&uv__loops_lock);
}