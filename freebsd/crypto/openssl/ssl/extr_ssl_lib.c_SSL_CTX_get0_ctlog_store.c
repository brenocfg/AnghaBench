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
struct TYPE_3__ {int /*<<< orphan*/  const* ctlog_store; } ;
typedef  TYPE_1__ SSL_CTX ;
typedef  int /*<<< orphan*/  CTLOG_STORE ;

/* Variables and functions */

const CTLOG_STORE *SSL_CTX_get0_ctlog_store(const SSL_CTX *ctx)
{
    return ctx->ctlog_store;
}