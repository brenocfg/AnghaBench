#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  md3Header_t ;
struct TYPE_9__ {int /*<<< orphan*/ * (* Malloc ) (size_t) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* clear_model ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* model_getters ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;int /*<<< orphan*/  (* find_model ) (int /*<<< orphan*/ ,char const*) ;} ;
struct TYPE_6__ {size_t (* serialised_model_size ) (int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  (* serialise_model ) (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  userdata; TYPE_2__ hooks; TYPE_1__ calls; } ;
typedef  int /*<<< orphan*/  DeepmindModelGetters ;
typedef  TYPE_3__ DeepmindContext ;

/* Variables and functions */
 TYPE_3__* dmlab_context () ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_4__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 size_t stub3 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * stub4 (size_t) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 

qboolean R_DMLabToMD3(const char *mod_name, md3Header_t **mod_md3) {
  DeepmindContext *ctx = dmlab_context();

  // Load the model in the context.
  if (!ctx->hooks.find_model(ctx->userdata, mod_name)) {
    return qfalse;
  }

  // Retrieve the model's accessor API.
  DeepmindModelGetters model_getters;
  void* model_data;
  ctx->hooks.model_getters(ctx->userdata, &model_getters, &model_data);

  // Compute the required buffer size.
  size_t buffer_len =
      ctx->calls.serialised_model_size(&model_getters, model_data);

  // Allocate the data.
  *mod_md3 = ri.Malloc(buffer_len);

  // Fill up the buffer with MD3 model data.
  ctx->calls.serialise_model(&model_getters, model_data, *mod_md3);

  // Clear the loaded model.
  ctx->hooks.clear_model(ctx->userdata);

  return qtrue;
}