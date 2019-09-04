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
struct TYPE_4__ {char const* (* custom_action_discrete_name ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
struct TYPE_5__ {TYPE_3__* dm_ctx; } ;
typedef  TYPE_2__ GameContext ;
typedef  TYPE_3__ DeepmindContext ;

/* Variables and functions */
 int ARRAY_LEN (char const**) ; 
 char const** kActionNames ; 
 char const* stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char* dmlab_action_discrete_name(void* context, int discrete_idx) {
  if (discrete_idx < ARRAY_LEN(kActionNames)) {
    return kActionNames[discrete_idx];
  } else {
    GameContext* gc = context;
    DeepmindContext* ctx = gc->dm_ctx;
    return ctx->hooks.custom_action_discrete_name(
        ctx->userdata, discrete_idx - ARRAY_LEN(kActionNames));
  }
}