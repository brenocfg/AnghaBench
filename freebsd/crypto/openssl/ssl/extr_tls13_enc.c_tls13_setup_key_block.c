#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cipher; } ;
struct TYPE_9__ {TYPE_2__* s3; TYPE_5__* session; } ;
struct TYPE_7__ {int /*<<< orphan*/  const* new_hash; int /*<<< orphan*/  const* new_sym_enc; int /*<<< orphan*/  new_cipher; } ;
struct TYPE_8__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS13_SETUP_KEY_BLOCK ; 
 int /*<<< orphan*/  SSL_R_CIPHER_OR_HASH_UNAVAILABLE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_cipher_get_evp (TYPE_5__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int tls13_setup_key_block(SSL *s)
{
    const EVP_CIPHER *c;
    const EVP_MD *hash;

    s->session->cipher = s->s3->tmp.new_cipher;
    if (!ssl_cipher_get_evp(s->session, &c, &hash, NULL, NULL, NULL, 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_SETUP_KEY_BLOCK,
                 SSL_R_CIPHER_OR_HASH_UNAVAILABLE);
        return 0;
    }

    s->s3->tmp.new_sym_enc = c;
    s->s3->tmp.new_hash = hash;

    return 1;
}