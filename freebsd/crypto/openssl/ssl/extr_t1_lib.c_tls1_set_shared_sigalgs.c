#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_12__ {size_t client_sigalgslen; size_t conf_sigalgslen; int /*<<< orphan*/ * conf_sigalgs; int /*<<< orphan*/ * client_sigalgs; } ;
struct TYPE_11__ {size_t shared_sigalgslen; int options; int /*<<< orphan*/  const** shared_sigalgs; TYPE_2__* s3; int /*<<< orphan*/  server; TYPE_4__* cert; } ;
struct TYPE_9__ {size_t peer_sigalgslen; int /*<<< orphan*/ * peer_sigalgs; } ;
struct TYPE_10__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  SIGALG_LOOKUP ;
typedef  TYPE_4__ CERT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ ** OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  SSL_F_TLS1_SET_SHARED_SIGALGS ; 
 int SSL_OP_CIPHER_SERVER_PREFERENCE ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t tls12_get_psigalgs (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 size_t tls12_shared_sigalgs (TYPE_3__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 unsigned int tls1_suiteb (TYPE_3__*) ; 

__attribute__((used)) static int tls1_set_shared_sigalgs(SSL *s)
{
    const uint16_t *pref, *allow, *conf;
    size_t preflen, allowlen, conflen;
    size_t nmatch;
    const SIGALG_LOOKUP **salgs = NULL;
    CERT *c = s->cert;
    unsigned int is_suiteb = tls1_suiteb(s);

    OPENSSL_free(s->shared_sigalgs);
    s->shared_sigalgs = NULL;
    s->shared_sigalgslen = 0;
    /* If client use client signature algorithms if not NULL */
    if (!s->server && c->client_sigalgs && !is_suiteb) {
        conf = c->client_sigalgs;
        conflen = c->client_sigalgslen;
    } else if (c->conf_sigalgs && !is_suiteb) {
        conf = c->conf_sigalgs;
        conflen = c->conf_sigalgslen;
    } else
        conflen = tls12_get_psigalgs(s, 0, &conf);
    if (s->options & SSL_OP_CIPHER_SERVER_PREFERENCE || is_suiteb) {
        pref = conf;
        preflen = conflen;
        allow = s->s3->tmp.peer_sigalgs;
        allowlen = s->s3->tmp.peer_sigalgslen;
    } else {
        allow = conf;
        allowlen = conflen;
        pref = s->s3->tmp.peer_sigalgs;
        preflen = s->s3->tmp.peer_sigalgslen;
    }
    nmatch = tls12_shared_sigalgs(s, NULL, pref, preflen, allow, allowlen);
    if (nmatch) {
        if ((salgs = OPENSSL_malloc(nmatch * sizeof(*salgs))) == NULL) {
            SSLerr(SSL_F_TLS1_SET_SHARED_SIGALGS, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        nmatch = tls12_shared_sigalgs(s, salgs, pref, preflen, allow, allowlen);
    } else {
        salgs = NULL;
    }
    s->shared_sigalgs = salgs;
    s->shared_sigalgslen = nmatch;
    return 1;
}