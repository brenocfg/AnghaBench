#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* s3; int /*<<< orphan*/ * pha_dgst; } ;
struct TYPE_6__ {int /*<<< orphan*/  handshake_dgst; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_MD_CTX_copy_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS13_SAVE_HANDSHAKE_DIGEST_FOR_PHA ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_digest_cached_records (TYPE_2__*,int) ; 

int tls13_save_handshake_digest_for_pha(SSL *s)
{
    if (s->pha_dgst == NULL) {
        if (!ssl3_digest_cached_records(s, 1))
            /* SSLfatal() already called */
            return 0;

        s->pha_dgst = EVP_MD_CTX_new();
        if (s->pha_dgst == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS13_SAVE_HANDSHAKE_DIGEST_FOR_PHA,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
        if (!EVP_MD_CTX_copy_ex(s->pha_dgst,
                                s->s3->handshake_dgst)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS13_SAVE_HANDSHAKE_DIGEST_FOR_PHA,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }
    return 1;
}