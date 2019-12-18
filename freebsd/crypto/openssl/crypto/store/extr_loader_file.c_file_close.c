#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  file; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_9__ {TYPE_2__ file; TYPE_1__ dir; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__ _; } ;
typedef  TYPE_4__ OSSL_STORE_LOADER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_DIR_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_STORE_LOADER_CTX_free (TYPE_4__*) ; 
 scalar_t__ is_dir ; 

__attribute__((used)) static int file_close(OSSL_STORE_LOADER_CTX *ctx)
{
    if (ctx->type == is_dir) {
        OPENSSL_DIR_end(&ctx->_.dir.ctx);
    } else {
        BIO_free_all(ctx->_.file.file);
    }
    OSSL_STORE_LOADER_CTX_free(ctx);
    return 1;
}