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
typedef  int /*<<< orphan*/  h2o_cache_t ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 scalar_t__ SSL_CTX_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ssl_session_cache_index () ; 

h2o_cache_t *h2o_socket_ssl_get_session_cache(SSL_CTX *ctx)
{
    return (h2o_cache_t *)SSL_CTX_get_ex_data(ctx, get_ssl_session_cache_index());
}