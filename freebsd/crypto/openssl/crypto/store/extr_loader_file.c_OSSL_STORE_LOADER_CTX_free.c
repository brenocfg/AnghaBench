#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* last_handler; int /*<<< orphan*/ * last_handler_ctx; } ;
struct TYPE_8__ {TYPE_5__* uri; } ;
struct TYPE_10__ {TYPE_2__ file; TYPE_1__ dir; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_3__ _; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* destroy_ctx ) (int /*<<< orphan*/ **) ;} ;
typedef  TYPE_5__ OSSL_STORE_LOADER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_5__*) ; 
 scalar_t__ is_dir ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void OSSL_STORE_LOADER_CTX_free(OSSL_STORE_LOADER_CTX *ctx)
{
    if (ctx->type == is_dir) {
        OPENSSL_free(ctx->_.dir.uri);
    } else {
        if (ctx->_.file.last_handler != NULL) {
            ctx->_.file.last_handler->destroy_ctx(&ctx->_.file.last_handler_ctx);
            ctx->_.file.last_handler_ctx = NULL;
            ctx->_.file.last_handler = NULL;
        }
    }
    OPENSSL_free(ctx);
}