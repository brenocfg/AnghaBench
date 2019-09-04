#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* (* next_map ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* add_bots ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
struct TYPE_7__ {char const* engine_frame_period_msec; TYPE_3__* dm_ctx; } ;
typedef  TYPE_2__ GameContext ;
typedef  TYPE_3__ DeepmindContext ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd_ExecuteString (char*) ; 
 int /*<<< orphan*/  Com_Frame () ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  make_map (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 char* va (char*,char const*) ; 

__attribute__((used)) static void dev_map(GameContext* gc) {
  DeepmindContext* ctx = gc->dm_ctx;
  Cvar_Set("fixedtime", va("%d", gc->engine_frame_period_msec));
  const char* next_map = ctx->hooks.next_map(ctx->userdata);
  if (next_map[0] == '\0') {
    Cmd_ExecuteString("map_restart 0");
    Cmd_ExecuteString("updatecustomitems");
    Com_Frame();
  } else {
    if (!make_map(gc, next_map)) {
      perror(va("Didn't find map '%s'\n", next_map));
      exit(1);
    }
    Cmd_ExecuteString(va("devmap \"%s\"", next_map));
    Com_Frame();
    ctx->hooks.add_bots(ctx->userdata);
  }
}