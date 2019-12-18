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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int use_etm; } ;
struct TYPE_5__ {int options; TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int SSL_OP_NO_ENCRYPT_THEN_MAC ; 

int tls_parse_ctos_etm(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                       size_t chainidx)
{
    if (!(s->options & SSL_OP_NO_ENCRYPT_THEN_MAC))
        s->ext.use_etm = 1;

    return 1;
}