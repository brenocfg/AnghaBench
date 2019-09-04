#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ error; int /*<<< orphan*/  error_message; scalar_t__ is_recording; } ;
struct TYPE_9__ {int is_connecting; int map_loaded; TYPE_5__* recording_ctx; TYPE_2__* dm_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_error_message ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
typedef  TYPE_3__ GameContext ;

/* Variables and functions */
 scalar_t__ DMLAB_RECORDING_ERROR_NONE ; 
 int /*<<< orphan*/  dev_map (TYPE_3__*) ; 
 int /*<<< orphan*/  dmlab_start_recording (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool start_server(GameContext* gc) {
  dev_map(gc);
  if (gc->recording_ctx->is_recording) {
    dmlab_start_recording(gc->recording_ctx);
    if (gc->recording_ctx->error != DMLAB_RECORDING_ERROR_NONE) {
      gc->dm_ctx->hooks.set_error_message(gc->dm_ctx->userdata,
                                          gc->recording_ctx->error_message);
      return false;
    }
  }
  gc->is_connecting = true;
  gc->map_loaded = false;
  return true;
}