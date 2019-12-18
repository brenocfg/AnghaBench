#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ssl_cert; } ;
typedef  TYPE_1__ serf_ssl_certificate_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/ * PEM_read_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERF_ERROR_SSL_CERT_FAILED ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 

apr_status_t serf_ssl_load_cert_file(
    serf_ssl_certificate_t **cert,
    const char *file_path,
    apr_pool_t *pool)
{
    FILE *fp = fopen(file_path, "r");

    if (fp) {
        X509 *ssl_cert = PEM_read_X509(fp, NULL, NULL, NULL);
        fclose(fp);

        if (ssl_cert) {
            *cert = apr_palloc(pool, sizeof(serf_ssl_certificate_t));
            (*cert)->ssl_cert = ssl_cert;

            return APR_SUCCESS;
        }
    }

    return SERF_ERROR_SSL_CERT_FAILED;
}