#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
struct TYPE_21__ {size_t size; TYPE_5__** entries; } ;
struct TYPE_20__ {size_t size; TYPE_7__** entries; } ;
struct TYPE_19__ {size_t size; TYPE_6__** entries; } ;
struct TYPE_22__ {TYPE_3__ _loggers; TYPE_2__ _filters; TYPE_1__ handlers; } ;
typedef  TYPE_4__ h2o_pathconf_t ;
struct TYPE_23__ {int /*<<< orphan*/  (* on_context_init ) (TYPE_5__*,TYPE_8__*) ;} ;
typedef  TYPE_5__ h2o_logger_t ;
struct TYPE_24__ {int /*<<< orphan*/  (* on_context_init ) (TYPE_6__*,TYPE_8__*) ;} ;
typedef  TYPE_6__ h2o_handler_t ;
struct TYPE_25__ {int /*<<< orphan*/  (* on_context_init ) (TYPE_7__*,TYPE_8__*) ;} ;
typedef  TYPE_7__ h2o_filter_t ;
struct TYPE_18__ {size_t size; TYPE_4__** entries; } ;
struct TYPE_26__ {TYPE_15__ _pathconfs_inited; } ;
typedef  TYPE_8__ h2o_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_15__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,TYPE_8__*) ; 

void h2o_context_init_pathconf_context(h2o_context_t *ctx, h2o_pathconf_t *pathconf)
{
    /* add pathconf to the inited list (or return if already inited) */
    size_t i;
    for (i = 0; i != ctx->_pathconfs_inited.size; ++i)
        if (ctx->_pathconfs_inited.entries[i] == pathconf)
            return;
    h2o_vector_reserve(NULL, &ctx->_pathconfs_inited, ctx->_pathconfs_inited.size + 1);
    ctx->_pathconfs_inited.entries[ctx->_pathconfs_inited.size++] = pathconf;

#define DOIT(type, list)                                                                                                           \
    do {                                                                                                                           \
        size_t i;                                                                                                                  \
        for (i = 0; i != pathconf->list.size; ++i) {                                                                               \
            type *o = pathconf->list.entries[i];                                                                                   \
            if (o->on_context_init != NULL)                                                                                        \
                o->on_context_init(o, ctx);                                                                                        \
        }                                                                                                                          \
    } while (0)

    DOIT(h2o_handler_t, handlers);
    DOIT(h2o_filter_t, _filters);
    DOIT(h2o_logger_t, _loggers);

#undef DOIT
}