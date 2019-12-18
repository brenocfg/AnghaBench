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
struct TYPE_3__ {void* record_padding_arg; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */

void SSL_CTX_set_record_padding_callback_arg(SSL_CTX *ctx, void *arg)
{
    ctx->record_padding_arg = arg;
}