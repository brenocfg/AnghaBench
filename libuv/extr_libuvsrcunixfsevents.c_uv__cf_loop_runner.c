#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cf_sem; TYPE_2__* cf_state; } ;
typedef  TYPE_1__ uv_loop_t ;
struct TYPE_4__ {int /*<<< orphan*/  signal_source; int /*<<< orphan*/  loop; } ;
typedef  TYPE_2__ uv__cf_loop_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  pCFRunLoopAddSource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCFRunLoopGetCurrent () ; 
 int /*<<< orphan*/  pCFRunLoopRemoveSource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCFRunLoopRun () ; 
 int /*<<< orphan*/ * pkCFRunLoopDefaultMode ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* uv__cf_loop_runner(void* arg) {
  uv_loop_t* loop;
  uv__cf_loop_state_t* state;

  loop = arg;
  state = loop->cf_state;
  state->loop = pCFRunLoopGetCurrent();

  pCFRunLoopAddSource(state->loop,
                      state->signal_source,
                      *pkCFRunLoopDefaultMode);

  uv_sem_post(&loop->cf_sem);

  pCFRunLoopRun();
  pCFRunLoopRemoveSource(state->loop,
                         state->signal_source,
                         *pkCFRunLoopDefaultMode);

  return NULL;
}