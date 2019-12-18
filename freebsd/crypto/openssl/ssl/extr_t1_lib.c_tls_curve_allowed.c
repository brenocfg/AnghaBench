#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  nid; int /*<<< orphan*/  secbits; } ;
typedef  TYPE_1__ TLS_GROUP_INFO ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int TLS_CURVE_CHAR2 ; 
 int ssl_security (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 TYPE_1__* tls1_group_id_lookup (int) ; 

int tls_curve_allowed(SSL *s, uint16_t curve, int op)
{
    const TLS_GROUP_INFO *cinfo = tls1_group_id_lookup(curve);
    unsigned char ctmp[2];

    if (cinfo == NULL)
        return 0;
# ifdef OPENSSL_NO_EC2M
    if (cinfo->flags & TLS_CURVE_CHAR2)
        return 0;
# endif
    ctmp[0] = curve >> 8;
    ctmp[1] = curve & 0xff;
    return ssl_security(s, op, cinfo->secbits, cinfo->nid, (void *)ctmp);
}