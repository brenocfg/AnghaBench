#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int sig_idx; } ;
struct TYPE_12__ {TYPE_2__* cert; } ;
struct TYPE_11__ {TYPE_1__* pkeys; } ;
struct TYPE_10__ {int /*<<< orphan*/  privatekey; int /*<<< orphan*/  x509; } ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ SIGALG_LOOKUP ;

/* Variables and functions */
 int check_cert_usable (TYPE_3__*,TYPE_4__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_has_cert (TYPE_3__*,int) ; 

__attribute__((used)) static int has_usable_cert(SSL *s, const SIGALG_LOOKUP *sig, int idx)
{
    /* TLS 1.2 callers can override sig->sig_idx, but not TLS 1.3 callers. */
    if (idx == -1)
        idx = sig->sig_idx;
    if (!ssl_has_cert(s, idx))
        return 0;

    return check_cert_usable(s, sig, s->cert->pkeys[idx].x509,
                             s->cert->pkeys[idx].privatekey);
}