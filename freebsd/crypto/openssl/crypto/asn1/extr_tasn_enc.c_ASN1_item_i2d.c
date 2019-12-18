#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int asn1_item_flags_i2d (int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ASN1_item_i2d(ASN1_VALUE *val, unsigned char **out, const ASN1_ITEM *it)
{
    return asn1_item_flags_i2d(val, out, it, 0);
}