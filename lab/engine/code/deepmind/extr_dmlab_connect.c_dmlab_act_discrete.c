#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* custom_action_discrete_apply ) (int /*<<< orphan*/ ,int const*) ;int /*<<< orphan*/  (* set_actions ) (int /*<<< orphan*/ ,float,float,int,int,int,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
struct TYPE_5__ {int is_connecting; TYPE_3__* dm_ctx; scalar_t__ is_server; } ;
typedef  TYPE_2__ GameContext ;
typedef  TYPE_3__ DeepmindContext ;

/* Variables and functions */
 int ARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kActionNames ; 
 size_t kActions_Crouch ; 
 size_t kActions_Fire ; 
 size_t kActions_Jump ; 
 size_t kActions_LookDownUp ; 
 size_t kActions_LookLeftRight ; 
 size_t kActions_MoveBackForward ; 
 size_t kActions_StrafeLeftRight ; 
 int const kPixelsPerFrameToDegreesPerMilliseconds ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,float,float,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static void dmlab_act_discrete(void* context, const int act_d[]) {
  GameContext* gc = context;
  gc->is_connecting = false;
  if (gc->is_server) return;
  DeepmindContext* ctx = gc->dm_ctx;
  int rightmove = act_d[kActions_StrafeLeftRight] * 127;
  int forwardmove = act_d[kActions_MoveBackForward] * 127;
  float yaw =
      -act_d[kActions_LookLeftRight] * kPixelsPerFrameToDegreesPerMilliseconds;
  float pitch =
      act_d[kActions_LookDownUp] * kPixelsPerFrameToDegreesPerMilliseconds;
  int upmove = (act_d[kActions_Jump] - act_d[kActions_Crouch]) * 127;
  int buttons = act_d[kActions_Fire];

  ctx->hooks.set_actions(ctx->userdata, pitch, yaw, forwardmove, rightmove,
                         upmove, buttons);
  ctx->hooks.custom_action_discrete_apply(ctx->userdata,
                                          act_d + ARRAY_LEN(kActionNames));
}