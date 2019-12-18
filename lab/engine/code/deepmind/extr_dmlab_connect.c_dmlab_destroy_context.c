#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  (* MakeCurrent ) () ;} ;
struct TYPE_12__ {scalar_t__ id; } ;
struct TYPE_11__ {scalar_t__ id; } ;
struct TYPE_10__ {scalar_t__ id; } ;
struct TYPE_13__ {TYPE_3__ custom_view; TYPE_2__ depth; TYPE_1__ rgb; } ;
struct TYPE_14__ {scalar_t__ error; char* error_message; struct TYPE_14__* image_buffer; struct TYPE_14__* temp_buffer; struct TYPE_14__* recording_ctx; TYPE_4__ pbos; scalar_t__ is_video; scalar_t__ is_recording; int /*<<< orphan*/ * dm_ctx; } ;
typedef  TYPE_5__ GameContext ;
typedef  int /*<<< orphan*/  DeepmindContext ;

/* Variables and functions */
 scalar_t__ DMLAB_RECORDING_ERROR_NONE ; 
 int /*<<< orphan*/  DMLabUnloadIOQ3Module () ; 
 int /*<<< orphan*/  GLimp_Shutdown () ; 
 int /*<<< orphan*/  dmlab_release_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmlab_stop_recording (TYPE_5__*) ; 
 int /*<<< orphan*/  dmlab_stop_video (TYPE_5__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  qglDeleteBuffers (int,scalar_t__*) ; 
 TYPE_6__ re ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void dmlab_destroy_context(void* context) {
  GameContext* gc = context;
  DeepmindContext* ctx = gc->dm_ctx;

  if (gc->recording_ctx->is_recording) {
    dmlab_stop_recording(gc->recording_ctx);
  }
  if (gc->recording_ctx->is_video) {
    dmlab_stop_video(gc->recording_ctx);
  }
  if (gc->recording_ctx->error != DMLAB_RECORDING_ERROR_NONE) {
    fprintf(stderr, "ERROR: %s", gc->recording_ctx->error_message);
  }

  if (gc->pbos.rgb.id || gc->pbos.depth.id || gc->pbos.custom_view.id) {
    re.MakeCurrent();
    if (gc->pbos.rgb.id) {
      qglDeleteBuffers(1, &gc->pbos.rgb.id);
    }

    if (gc->pbos.depth.id) {
      qglDeleteBuffers(1, &gc->pbos.depth.id);
    }

    if (gc->pbos.custom_view.id) {
      qglDeleteBuffers(1, &gc->pbos.custom_view.id);
    }
  }

  dmlab_release_context(ctx);
  free(gc->recording_ctx);
  free(gc->temp_buffer);
  free(gc->image_buffer);
  free(gc);
  GLimp_Shutdown();
  DMLabUnloadIOQ3Module();
}