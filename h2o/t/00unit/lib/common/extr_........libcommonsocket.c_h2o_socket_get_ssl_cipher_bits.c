#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* aead; } ;
typedef  TYPE_3__ ptls_cipher_suite_t ;
struct TYPE_10__ {TYPE_2__* ssl; } ;
typedef  TYPE_4__ h2o_socket_t ;
struct TYPE_8__ {int /*<<< orphan*/ * ossl; int /*<<< orphan*/ * ptls; } ;
struct TYPE_7__ {scalar_t__ key_size; } ;

/* Variables and functions */
 int SSL_get_cipher_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* ptls_get_cipher (int /*<<< orphan*/ *) ; 

int h2o_socket_get_ssl_cipher_bits(h2o_socket_t *sock)
{
    if (sock->ssl != NULL) {
        if (sock->ssl->ptls != NULL) {
            ptls_cipher_suite_t *cipher = ptls_get_cipher(sock->ssl->ptls);
            if (cipher == NULL)
                return 0;
            return (int)cipher->aead->key_size;
        } else if (sock->ssl->ossl != NULL) {
            return SSL_get_cipher_bits(sock->ssl->ossl, NULL);
        }
    }
    return 0;
}