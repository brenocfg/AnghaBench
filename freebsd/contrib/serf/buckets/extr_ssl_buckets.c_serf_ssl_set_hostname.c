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
struct TYPE_3__ {int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ serf_ssl_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int SSL_set_tlsext_host_name (int /*<<< orphan*/ ,char const*) ; 

apr_status_t serf_ssl_set_hostname(serf_ssl_context_t *context,
                                   const char * hostname)
{
#ifdef SSL_set_tlsext_host_name
    if (SSL_set_tlsext_host_name(context->ssl, hostname) != 1) {
        ERR_clear_error();
    }
#endif
    return APR_SUCCESS;
}