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
struct TYPE_3__ {int modified; scalar_t__ len; int /*<<< orphan*/ * enc; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;
typedef  TYPE_1__ ASN1_ENCODING ;

/* Variables and functions */
 TYPE_1__* asn1_get_enc_ptr (int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 

void asn1_enc_init(ASN1_VALUE **pval, const ASN1_ITEM *it)
{
    ASN1_ENCODING *enc;
    enc = asn1_get_enc_ptr(pval, it);
    if (enc) {
        enc->enc = NULL;
        enc->len = 0;
        enc->modified = 1;
    }
}