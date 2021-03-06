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
struct TYPE_4__ {int (* custom_action_discrete_count ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
struct TYPE_5__ {scalar_t__ is_server; TYPE_3__* dm_ctx; } ;
typedef  TYPE_2__ GameContext ;
typedef  TYPE_3__ DeepmindContext ;

/* Variables and functions */
 int ARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kActionNames ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmlab_action_discrete_count(void* context) {
  GameContext* gc = context;
  DeepmindContext* ctx = gc->dm_ctx;
  return gc->is_server
             ? 0
             : ARRAY_LEN(kActionNames) +
                   ctx->hooks.custom_action_discrete_count(ctx->userdata);
}