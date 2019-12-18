#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  db; TYPE_1__* db_meth; } ;
typedef  TYPE_2__ X509V3_CTX ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_string ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void X509V3_string_free(X509V3_CTX *ctx, char *str)
{
    if (!str)
        return;
    if (ctx->db_meth->free_string)
        ctx->db_meth->free_string(ctx->db, str);
}