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
struct TYPE_3__ {void* default_passwd_callback_userdata; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */

void SSL_CTX_set_default_passwd_cb_userdata(SSL_CTX *ctx, void *u)
{
    ctx->default_passwd_callback_userdata = u;
}