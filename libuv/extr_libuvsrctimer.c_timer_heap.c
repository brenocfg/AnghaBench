#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  timer_heap; } ;
typedef  TYPE_1__ uv_loop_t ;
struct heap {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct heap *timer_heap(const uv_loop_t* loop) {
#ifdef _WIN32
  return (struct heap*) loop->timer_heap;
#else
  return (struct heap*) &loop->timer_heap;
#endif
}