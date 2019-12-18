#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  (* MakeCurrent ) () ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* clear ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int (* map_loaded ) (int /*<<< orphan*/ ) ;int (* start ) (int /*<<< orphan*/ ,int,int) ;TYPE_1__ events; int /*<<< orphan*/  (* set_error_message ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  userdata; TYPE_2__ hooks; } ;
struct TYPE_15__ {int current_screen_rendered; int map_loaded; double total_engine_time_msec; double score; int first_start; int is_map_loading; scalar_t__ is_client_only; scalar_t__ is_server; scalar_t__ step; scalar_t__ is_connecting; int /*<<< orphan*/  init_called; TYPE_4__* dm_ctx; } ;
struct TYPE_12__ {scalar_t__ state; } ;
typedef  TYPE_3__ GameContext ;
typedef  TYPE_4__ DeepmindContext ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 int EAGAIN ; 
 int INT_MAX ; 
 TYPE_11__ clc ; 
 int /*<<< orphan*/  connect_client (TYPE_3__*) ; 
 int connecting (TYPE_3__*) ; 
 int first_start (TYPE_3__*) ; 
 int /*<<< orphan*/  load_map (TYPE_3__*) ; 
 TYPE_6__ re ; 
 int /*<<< orphan*/  start_server (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 () ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int stub5 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub6 () ; 
 scalar_t__ stub7 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmlab_start(void* context, int episode_id, int seed) {
  // Make seed a non-negative integer.
  seed = (seed < 0) ? seed + 1 + INT_MAX : seed;
  GameContext* gc = context;
  DeepmindContext* ctx = gc->dm_ctx;
  if (!gc->init_called) {
    ctx->hooks.set_error_message(ctx->userdata,
                                 "'init' must be called before 'start. See "
                                 "documentation in env_c_api.h'\n");

    return 1;
  }
  gc->current_screen_rendered = false;
  if (gc->is_connecting) {
    re.MakeCurrent();
    int err = connecting(gc);
    if (err == 0 && !gc->map_loaded) {
      err = ctx->hooks.map_loaded(ctx->userdata);
      gc->map_loaded = true;
    }
    return err;
  }
  ctx->hooks.events.clear(ctx->userdata);
  gc->step = 0;
  gc->total_engine_time_msec = 0.0;
  gc->score = 0.0;

  int err = ctx->hooks.start(ctx->userdata, episode_id, seed);
  if (err != 0) {
    return err;
  }

  if (!gc->first_start) {
    int err = first_start(gc);
    if (err != 0) {
      return err;
    }
    gc->first_start = true;
  }

  re.MakeCurrent();
  if (gc->is_client_only) {
    connect_client(gc);
  } else if (gc->is_server) {
    if (!start_server(gc)) {
      return 1;
    }
  } else {
    if (!load_map(gc)) {
      return 1;
    }
    if (ctx->hooks.map_loaded(ctx->userdata) != 0) {
      return 1;
    }
  }

  gc->is_map_loading = false;
  if (gc->is_client_only) {
    return clc.state < CA_ACTIVE ? EAGAIN : 0;
  }
  return 0;
}