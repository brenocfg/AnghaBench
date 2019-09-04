#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ssl; } ;
typedef  TYPE_2__ h2o_socket_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ossl; } ;

/* Variables and functions */
 int SSL_get_cipher_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int h2o_socket_get_ssl_cipher_bits(h2o_socket_t *sock)
{
    if (sock->ssl != NULL) {
#if H2O_USE_PICOTLS
        if (sock->ssl->ptls != NULL) {
            ptls_cipher_suite_t *cipher = ptls_get_cipher(sock->ssl->ptls);
            if (cipher == NULL)
                return 0;
            return (int)cipher->aead->key_size;
        } else
#endif
            if (sock->ssl->ossl != NULL)
            return SSL_get_cipher_bits(sock->ssl->ossl, NULL);
    }
    return 0;
}