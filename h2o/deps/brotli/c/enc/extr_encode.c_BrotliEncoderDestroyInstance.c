#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* brotli_free_func ) (void*,TYPE_1__*) ;
struct TYPE_7__ {void* opaque; int /*<<< orphan*/  (* free_func ) (void*,TYPE_1__*) ;} ;
struct TYPE_6__ {TYPE_2__ memory_manager_; } ;
typedef  TYPE_2__ MemoryManager ;
typedef  TYPE_1__ BrotliEncoderState ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliEncoderCleanupState (TYPE_1__*) ; 

void BrotliEncoderDestroyInstance(BrotliEncoderState* state) {
  if (!state) {
    return;
  } else {
    MemoryManager* m = &state->memory_manager_;
    brotli_free_func free_func = m->free_func;
    void* opaque = m->opaque;
    BrotliEncoderCleanupState(state);
    free_func(opaque, state);
  }
}