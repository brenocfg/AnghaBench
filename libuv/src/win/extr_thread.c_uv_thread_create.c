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
typedef  int /*<<< orphan*/  uv_thread_t ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ uv_thread_options_t ;

/* Variables and functions */
 int /*<<< orphan*/  UV_THREAD_NO_FLAGS ; 
 int uv_thread_create_ex (int /*<<< orphan*/ *,TYPE_1__*,void (*) (void*),void*) ; 

int uv_thread_create(uv_thread_t *tid, void (*entry)(void *arg), void *arg) {
  uv_thread_options_t params;
  params.flags = UV_THREAD_NO_FLAGS;
  return uv_thread_create_ex(tid, &params, entry, arg);
}