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
typedef  int /*<<< orphan*/  serf_ssl_need_cert_password_t ;
struct TYPE_3__ {int /*<<< orphan*/  cert_pw_success; void* cert_pw_cache_pool; void* cert_pw_userdata; int /*<<< orphan*/  cert_pw_callback; } ;
typedef  TYPE_1__ serf_ssl_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_pool_userdata_get (void**,char*,void*) ; 

void serf_ssl_client_cert_password_set(
    serf_ssl_context_t *context,
    serf_ssl_need_cert_password_t callback,
    void *data,
    void *cache_pool)
{
    context->cert_pw_callback = callback;
    context->cert_pw_userdata = data;
    context->cert_pw_cache_pool = cache_pool;
    if (context->cert_pw_cache_pool) {
        apr_pool_userdata_get((void**)&context->cert_pw_success,
                              "serf:ssl:certpw", cache_pool);
    }
}