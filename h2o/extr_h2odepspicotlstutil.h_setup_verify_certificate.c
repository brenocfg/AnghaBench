#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  super; } ;
typedef  TYPE_1__ ptls_openssl_verify_certificate_t ;
struct TYPE_6__ {int /*<<< orphan*/ * verify_certificate; } ;
typedef  TYPE_2__ ptls_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_openssl_init_verify_certificate (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void setup_verify_certificate(ptls_context_t *ctx)
{
    static ptls_openssl_verify_certificate_t vc;
    ptls_openssl_init_verify_certificate(&vc, NULL);
    ctx->verify_certificate = &vc.super;
}