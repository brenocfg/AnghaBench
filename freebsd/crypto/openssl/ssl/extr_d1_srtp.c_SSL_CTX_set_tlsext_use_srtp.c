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
struct TYPE_3__ {int /*<<< orphan*/  srtp_profiles; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 int ssl_ctx_make_profiles (char const*,int /*<<< orphan*/ *) ; 

int SSL_CTX_set_tlsext_use_srtp(SSL_CTX *ctx, const char *profiles)
{
    return ssl_ctx_make_profiles(profiles, &ctx->srtp_profiles);
}