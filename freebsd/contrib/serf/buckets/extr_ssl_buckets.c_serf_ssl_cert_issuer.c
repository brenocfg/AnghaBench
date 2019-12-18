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
struct TYPE_3__ {int /*<<< orphan*/  ssl_cert; } ;
typedef  TYPE_1__ serf_ssl_certificate_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  X509_NAME ;

/* Variables and functions */
 int /*<<< orphan*/ * X509_get_issuer_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * convert_X509_NAME_to_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

apr_hash_t *serf_ssl_cert_issuer(
    const serf_ssl_certificate_t *cert,
    apr_pool_t *pool)
{
    X509_NAME *issuer = X509_get_issuer_name(cert->ssl_cert);

    if (!issuer)
        return NULL;

    return convert_X509_NAME_to_table(issuer, pool);
}