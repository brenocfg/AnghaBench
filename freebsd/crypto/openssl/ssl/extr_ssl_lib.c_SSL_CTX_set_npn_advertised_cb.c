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
struct TYPE_4__ {void* npn_advertised_cb_arg; int /*<<< orphan*/  npn_advertised_cb; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;
typedef  int /*<<< orphan*/  SSL_CTX_npn_advertised_cb_func ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */

void SSL_CTX_set_npn_advertised_cb(SSL_CTX *ctx,
                                   SSL_CTX_npn_advertised_cb_func cb,
                                   void *arg)
{
    ctx->ext.npn_advertised_cb = cb;
    ctx->ext.npn_advertised_cb_arg = arg;
}