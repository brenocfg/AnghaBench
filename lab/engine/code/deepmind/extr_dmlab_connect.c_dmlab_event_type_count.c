#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* type_count ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ events; } ;
struct TYPE_8__ {int /*<<< orphan*/  userdata; TYPE_2__ hooks; } ;
struct TYPE_7__ {TYPE_4__* dm_ctx; } ;
typedef  TYPE_3__ GameContext ;
typedef  TYPE_4__ DeepmindContext ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmlab_event_type_count(void* context) {
  GameContext* gc = context;
  DeepmindContext* ctx = gc->dm_ctx;
  return ctx->hooks.events.type_count(ctx->userdata);
}