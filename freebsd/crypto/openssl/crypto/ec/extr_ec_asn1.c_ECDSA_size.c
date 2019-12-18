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
struct TYPE_3__ {int length; unsigned char* data; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  TYPE_1__ ASN1_INTEGER ;

/* Variables and functions */
 int ASN1_object_size (int,int,int /*<<< orphan*/ ) ; 
 int EC_GROUP_order_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  V_ASN1_INTEGER ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int i2d_ASN1_INTEGER (TYPE_1__*,int /*<<< orphan*/ *) ; 

int ECDSA_size(const EC_KEY *r)
{
    int ret, i;
    ASN1_INTEGER bs;
    unsigned char buf[4];
    const EC_GROUP *group;

    if (r == NULL)
        return 0;
    group = EC_KEY_get0_group(r);
    if (group == NULL)
        return 0;

    i = EC_GROUP_order_bits(group);
    if (i == 0)
        return 0;
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