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
struct listener_ssl_config_t {scalar_t__ ctx; } ;
struct listener_config_t {int dummy; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int SSL_TLSEXT_ERR_OK ; 
 scalar_t__ SSL_get_SSL_CTX (int /*<<< orphan*/ *) ; 
 char* SSL_get_servername (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_SSL_CTX (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  TLSEXT_NAMETYPE_host_name ; 
 struct listener_ssl_config_t* resolve_sni (struct listener_config_t*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int on_sni_callback(SSL *ssl, int *ad, void *arg)
{
    struct listener_config_t *listener = arg;
    const char *server_name = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);

    if (server_name != NULL) {
        struct listener_ssl_config_t *resolved = resolve_sni(listener, server_name, strlen(server_name));
        if (resolved->ctx != SSL_get_SSL_CTX(ssl))
            SSL_set_SSL_CTX(ssl, resolved->ctx);
    }

    return SSL_TLSEXT_ERR_OK;
}