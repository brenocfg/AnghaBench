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
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ ptls_openssl_sign_certificate_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 

void ptls_openssl_dispose_sign_certificate(ptls_openssl_sign_certificate_t *self)
{
    EVP_PKEY_free(self->key);
}