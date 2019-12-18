#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_11__ {int sigandhash; } ;
struct TYPE_10__ {size_t shared_sigalgslen; TYPE_4__** shared_sigalgs; TYPE_2__* s3; } ;
struct TYPE_8__ {size_t peer_cert_sigalgslen; int /*<<< orphan*/ * peer_cert_sigalgs; } ;
struct TYPE_9__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ SIGALG_LOOKUP ;

/* Variables and functions */
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 int X509_get_signature_nid (int /*<<< orphan*/ *) ; 
 TYPE_4__* tls1_lookup_sigalg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tls1_check_sig_alg(SSL *s, X509 *x, int default_nid)
{
    int sig_nid, use_pc_sigalgs = 0;
    size_t i;
    const SIGALG_LOOKUP *sigalg;
    size_t sigalgslen;
    if (default_nid == -1)
        return 1;
    sig_nid = X509_get_signature_nid(x);
    if (default_nid)
        return sig_nid == default_nid ? 1 : 0;

    if (SSL_IS_TLS13(s) && s->s3->tmp.peer_cert_sigalgs != NULL) {
        /*
         * If we're in TLSv1.3 then we only get here if we're checking the
         * chain. If the peer has specified peer_cert_sigalgs then we use them
         * otherwise we default to normal sigalgs.
         */
        sigalgslen = s->s3->tmp.peer_cert_sigalgslen;
        use_pc_sigalgs = 1;
    } else {
        sigalgslen = s->shared_sigalgslen;
    }
    for (i = 0; i < sigalgslen; i++) {
        sigalg = use_pc_sigalgs
                 ? tls1_lookup_sigalg(s->s3->tmp.peer_cert_sigalgs[i])
                 : s->shared_sigalgs[i];
        if (sig_nid == sigalg->sigandhash)
            return 1;
    }
    return 0;
}