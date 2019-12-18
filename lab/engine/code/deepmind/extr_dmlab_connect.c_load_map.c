#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ error; int /*<<< orphan*/  error_message; scalar_t__ is_video; scalar_t__ is_demo; scalar_t__ is_recording; } ;
struct TYPE_14__ {int is_map_loading; TYPE_5__* recording_ctx; TYPE_2__* dm_ctx; int /*<<< orphan*/  map_start_frame; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* set_error_message ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
struct TYPE_11__ {int /*<<< orphan*/  framecount; } ;
typedef  TYPE_3__ GameContext ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Frame () ; 
 scalar_t__ DMLAB_RECORDING_ERROR_NONE ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  IN_Frame () ; 
 TYPE_10__ cls ; 
 scalar_t__ connecting (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_map (TYPE_3__*) ; 
 int dmlab_start_demo (TYPE_5__*) ; 
 int dmlab_start_recording (TYPE_5__*) ; 
 int dmlab_start_video (TYPE_5__*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool load_map(GameContext* gc) {
  gc->is_map_loading = true;
  dev_map(gc);
  if (!gc->recording_ctx->is_demo) {
    while (connecting(gc) == EAGAIN) {
    }
    // Players join team games in spectator mode. Leave 3 frames for player to
    // join the correct team.
    for (int i = 0; i < 3; ++i) {
      IN_Frame();
      Com_Frame();
    }
  }
  gc->map_start_frame = cls.framecount;

  bool demo_ok = true;
  if (gc->recording_ctx->is_recording) {
    demo_ok &= dmlab_start_recording(gc->recording_ctx);
  }
  if (gc->recording_ctx->is_demo) {
    demo_ok &= dmlab_start_demo(gc->recording_ctx);
  }
  if (demo_ok && gc->recording_ctx->is_video) {
    demo_ok &= dmlab_start_video(gc->recording_ctx);
  }
  if (gc->recording_ctx->error != DMLAB_RECORDING_ERROR_NONE) {
    gc->dm_ctx->hooks.set_error_message(gc->dm_ctx->userdata,
                                        gc->recording_ctx->error_message);
  }
  fflush(stdout);
  return demo_ok;
}