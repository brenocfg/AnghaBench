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
struct TYPE_2__ {void* (* local_realloc ) (void*,size_t) ;} ;

/* Variables and functions */
 void* stub1 (void*,size_t) ; 
 TYPE_1__ uv__allocator ; 
 int /*<<< orphan*/  uv__free (void*) ; 

void* uv__realloc(void* ptr, size_t size) {
  if (size > 0)
    return uv__allocator.local_realloc(ptr, size);
  uv__free(ptr);
  return NULL;
}