#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * uv_realloc_func ;
typedef  int /*<<< orphan*/ * uv_malloc_func ;
typedef  int /*<<< orphan*/ * uv_free_func ;
typedef  int /*<<< orphan*/ * uv_calloc_func ;
struct TYPE_2__ {int /*<<< orphan*/ * local_free; int /*<<< orphan*/ * local_calloc; int /*<<< orphan*/ * local_realloc; int /*<<< orphan*/ * local_malloc; } ;

/* Variables and functions */
 int UV_EINVAL ; 
 TYPE_1__ uv__allocator ; 

int uv_replace_allocator(uv_malloc_func malloc_func,
                         uv_realloc_func realloc_func,
                         uv_calloc_func calloc_func,
                         uv_free_func free_func) {
  if (malloc_func == NULL || realloc_func == NULL ||
      calloc_func == NULL || free_func == NULL) {
    return UV_EINVAL;
  }

  uv__allocator.local_malloc = malloc_func;
  uv__allocator.local_realloc = realloc_func;
  uv__allocator.local_calloc = calloc_func;
  uv__allocator.local_free = free_func;

  return 0;
}