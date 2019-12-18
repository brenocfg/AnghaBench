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
struct TYPE_6__ {int length; unsigned char* data; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  q; } ;
typedef  TYPE_1__ DSA ;
typedef  TYPE_2__ ASN1_INTEGER ;

/* Variables and functions */
 int ASN1_object_size (int,int,int /*<<< orphan*/ ) ; 
 int BN_num_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_INTEGER ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int i2d_ASN1_INTEGER (TYPE_2__*,int /*<<< orphan*/ *) ; 

int DSA_size(const DSA *r)
{
    int ret, i;
    ASN1_INTEGER bs;
    unsigned char buf[4];       /* 4 bytes looks really small. However,
                                 * i2d_ASN1_INTEGER() will not look beyond
                                 * the first byte, as long as the second
                                 * parameter is NULL. */

    i = BN_num_bits(r->q);
    bs.length = (i + 7) / 8;
    bs.data = buf;
    bs.type = V_ASN1_INTEGER;
    /* If the top bit is set the asn1 encoding is 1 larger. */
    buf[0] = 0xff;

    i = i2d_ASN1_INTEGER(&bs, NULL);
    i += i;                     /* r and s */
    ret = ASN1_object_size(1, i, V_ASN1_SEQUENCE);
    return ret;
}