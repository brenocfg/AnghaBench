#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  ErrorOnNul ; 
 int /*<<< orphan*/  NID_commonName ; 
 scalar_t__ SERF_ERROR_SSL_CERT_FAILED ; 
 int X509_NAME_get_text_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ *) ; 
 scalar_t__ get_subject_alt_names (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static apr_status_t validate_cert_hostname(X509 *server_cert, apr_pool_t *pool)
{
    char buf[1024];
    int length;
    apr_status_t ret;

    ret = get_subject_alt_names(NULL, server_cert, ErrorOnNul, NULL);
    if (ret) {
      return ret;
    } else {
        /* Fail if the subject's CN field contains \0 characters. */
        X509_NAME *subject = X509_get_subject_name(server_cert);
        if (!subject)
            return SERF_ERROR_SSL_CERT_FAILED;

        length = X509_NAME_get_text_by_NID(subject, NID_commonName, buf, 1024);
        if (length != -1)
            if (strlen(buf) != length)
                return SERF_ERROR_SSL_CERT_FAILED;
    }

    return APR_SUCCESS;
}