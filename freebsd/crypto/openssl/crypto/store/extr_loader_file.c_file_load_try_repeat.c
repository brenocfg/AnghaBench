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
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_7__ {TYPE_1__* last_handler; int /*<<< orphan*/ * last_handler_ctx; } ;
struct TYPE_8__ {TYPE_2__ file; } ;
struct TYPE_9__ {TYPE_3__ _; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy_ctx ) (int /*<<< orphan*/ **) ;int /*<<< orphan*/ * (* try_decode ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/  const*,void*) ;} ;
typedef  TYPE_4__ OSSL_STORE_LOADER_CTX ;
typedef  int /*<<< orphan*/  OSSL_STORE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ **) ; 

__attribute__((used)) static OSSL_STORE_INFO *file_load_try_repeat(OSSL_STORE_LOADER_CTX *ctx,
                                             const UI_METHOD *ui_method,
                                             void *ui_data)
{
    OSSL_STORE_INFO *result = NULL;
    int try_matchcount = 0;

    if (ctx->_.file.last_handler != NULL) {
        result =
            ctx->_.file.last_handler->try_decode(NULL, NULL, NULL, 0,
                                                 &ctx->_.file.last_handler_ctx,
                                                 &try_matchcount,
                                                 ui_method, ui_data);

        if (result == NULL) {
            ctx->_.file.last_handler->destroy_ctx(&ctx->_.file.last_handler_ctx);
            ctx->_.file.last_handler_ctx = NULL;
            ctx->_.file.last_handler = NULL;
        }
    }
    return result;
}