#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {TYPE_1__* s3; } ;
struct TYPE_5__ {int npn_seen; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 scalar_t__ SSL_IS_FIRST_HANDSHAKE (TYPE_2__*) ; 

int tls_parse_ctos_npn(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                       size_t chainidx)
{
    /*
     * We shouldn't accept this extension on a
     * renegotiation.
     */
    if (SSL_IS_FIRST_HANDSHAKE(s))
        s->s3->npn_seen = 1;

    return 1;
}