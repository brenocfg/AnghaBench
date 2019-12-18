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
struct TYPE_3__ {int /*<<< orphan*/ * base; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  RSA_CERTIFICATE ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * x509_from_pem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_certificate(ptls_iovec_t *dst)
{
    X509 *cert = x509_from_pem(RSA_CERTIFICATE);

    dst->base = NULL;
    dst->len = i2d_X509(cert, &dst->base);

    X509_free(cert);
}