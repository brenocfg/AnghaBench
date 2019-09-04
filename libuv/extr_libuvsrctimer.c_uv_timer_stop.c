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
struct TYPE_5__ {int /*<<< orphan*/  heap_node; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_timer_t ;
struct heap_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_remove (int /*<<< orphan*/ ,struct heap_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_heap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_less_than ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__is_active (TYPE_1__*) ; 

int uv_timer_stop(uv_timer_t* handle) {
  if (!uv__is_active(handle))
    return 0;

  heap_remove(timer_heap(handle->loop),
              (struct heap_node*) &handle->heap_node,
              timer_less_than);
  uv__handle_stop(handle);

  return 0;
}