#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dir_load; char* DYNAMIC_LIBNAME; int /*<<< orphan*/  dynamic_dso; int /*<<< orphan*/  dirs; } ;
typedef  TYPE_1__ dynamic_data_ctx ;

/* Variables and functions */
 int /*<<< orphan*/ * DSO_load (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* DSO_merge (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int sk_OPENSSL_STRING_num (int /*<<< orphan*/ ) ; 
 char* sk_OPENSSL_STRING_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int int_load(dynamic_data_ctx *ctx)
{
    int num, loop;
    /* Unless told not to, try a direct load */
    if ((ctx->dir_load != 2) && (DSO_load(ctx->dynamic_dso,
                                          ctx->DYNAMIC_LIBNAME, NULL,
                                          0)) != NULL)
        return 1;
    /* If we're not allowed to use 'dirs' or we have none, fail */
    if (!ctx->dir_load || (num = sk_OPENSSL_STRING_num(ctx->dirs)) < 1)
        return 0;
    for (loop = 0; loop < num; loop++) {
        const char *s = sk_OPENSSL_STRING_value(ctx->dirs, loop);
        char *merge = DSO_merge(ctx->dynamic_dso, ctx->DYNAMIC_LIBNAME, s);
        if (!merge)
            return 0;
        if (DSO_load(ctx->dynamic_dso, merge, NULL, 0)) {
            /* Found what we're looking for */
            OPENSSL_free(merge);
            return 1;
        }
        OPENSSL_free(merge);
    }
    return 0;
}