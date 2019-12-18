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
struct TYPE_3__ {int verify_mode; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */

int SSL_CTX_get_verify_mode(const SSL_CTX *ctx)
{
    return ctx->verify_mode;
}