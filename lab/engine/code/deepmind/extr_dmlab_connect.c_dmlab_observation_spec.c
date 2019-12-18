#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* custom_observation_spec ) (int /*<<< orphan*/ ,int,TYPE_3__*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
struct TYPE_9__ {int dims; int* shape; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int* map_frame_number_shape; int* image_shape; int height; int width; TYPE_4__* dm_ctx; } ;
typedef  TYPE_2__ GameContext ;
typedef  TYPE_3__ EnvCApi_ObservationSpec ;
typedef  TYPE_4__ DeepmindContext ;

/* Variables and functions */
 int ARRAY_LEN (char**) ; 
 int /*<<< orphan*/  EnvCApi_ObservationBytes ; 
 int /*<<< orphan*/  EnvCApi_ObservationDoubles ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char** kObservationNames ; 
#define  kObservations_BgrInterleaved 135 
#define  kObservations_BgrdInterleaved 134 
 int kObservations_MapFrameNumber ; 
#define  kObservations_RgbInterlaced 133 
#define  kObservations_RgbInterleaved 132 
#define  kObservations_RgbPlanar 131 
#define  kObservations_RgbdInterlaced 130 
#define  kObservations_RgbdInterleaved 129 
#define  kObservations_RgbdPlanar 128 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,TYPE_3__*) ; 

__attribute__((used)) static void dmlab_observation_spec(
    void* context, int observation_idx, EnvCApi_ObservationSpec* spec) {
  GameContext* gc = context;

  if (observation_idx == kObservations_MapFrameNumber) {
    spec->type = EnvCApi_ObservationDoubles;
    spec->dims = 1;
    spec->shape = gc->map_frame_number_shape;
  } else if (observation_idx < ARRAY_LEN(kObservationNames)) {
    spec->type = EnvCApi_ObservationBytes;
    spec->dims = 3;
    spec->shape = gc->image_shape;

    switch (observation_idx) {
      case kObservations_RgbInterlaced:
        fprintf(stderr, "Using deprecated observation format: '%s'\n",
                kObservationNames[observation_idx]);
        // FALLTHROUGH_INTENDED
      case kObservations_RgbInterleaved:
      case kObservations_BgrInterleaved:
        gc->image_shape[0] = gc->height;
        gc->image_shape[1] = gc->width;
        gc->image_shape[2] = 3;
        break;
      case kObservations_RgbdInterlaced:
        fprintf(stderr, "Using deprecated observation format: '%s'\n",
                kObservationNames[observation_idx]);
        // FALLTHROUGH_INTENDED
      case kObservations_RgbdInterleaved:
      case kObservations_BgrdInterleaved:
        gc->image_shape[0] = gc->height;
        gc->image_shape[1] = gc->width;
        gc->image_shape[2] = 4;
        break;
      case kObservations_RgbPlanar:
        gc->image_shape[0] = 3;
        gc->image_shape[1] = gc->height;
        gc->image_shape[2] = gc->width;
        break;
      case kObservations_RgbdPlanar:
        gc->image_shape[0] = 4;
        gc->image_shape[1] = gc->height;
        gc->image_shape[2] = gc->width;
        break;
    }
  } else {
    DeepmindContext* ctx = gc->dm_ctx;
    ctx->hooks.custom_observation_spec(
        ctx->userdata, observation_idx - ARRAY_LEN(kObservationNames), spec);
  }
}