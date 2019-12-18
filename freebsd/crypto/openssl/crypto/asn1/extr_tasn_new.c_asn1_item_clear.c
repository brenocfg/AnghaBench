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
struct TYPE_7__ {int /*<<< orphan*/  (* asn1_ex_clear ) (int /*<<< orphan*/ **,TYPE_1__ const*) ;} ;
struct TYPE_6__ {int itype; int /*<<< orphan*/  templates; TYPE_2__* funcs; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_ITEM ;
typedef  TYPE_2__ ASN1_EXTERN_FUNCS ;

/* Variables and functions */
#define  ASN1_ITYPE_CHOICE 133 
#define  ASN1_ITYPE_EXTERN 132 
#define  ASN1_ITYPE_MSTRING 131 
#define  ASN1_ITYPE_NDEF_SEQUENCE 130 
#define  ASN1_ITYPE_PRIMITIVE 129 
#define  ASN1_ITYPE_SEQUENCE 128 
 int /*<<< orphan*/  asn1_primitive_clear (int /*<<< orphan*/ **,TYPE_1__ const*) ; 
 int /*<<< orphan*/  asn1_template_clear (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,TYPE_1__ const*) ; 

__attribute__((used)) static void asn1_item_clear(ASN1_VALUE **pval, const ASN1_ITEM *it)
{
    const ASN1_EXTERN_FUNCS *ef;

    switch (it->itype) {

    case ASN1_ITYPE_EXTERN:
        ef = it->funcs;
        if (ef && ef->asn1_ex_clear)
            ef->asn1_ex_clear(pval, it);
        else
            *pval = NULL;
        break;

    case ASN1_ITYPE_PRIMITIVE:
        if (it->templates)
            asn1_template_clear(pval, it->templates);
        else
            asn1_primitive_clear(pval, it);
        break;

    case ASN1_ITYPE_MSTRING:
        asn1_primitive_clear(pval, it);
        break;

    case ASN1_ITYPE_CHOICE:
    case ASN1_ITYPE_SEQUENCE:
    case ASN1_ITYPE_NDEF_SEQUENCE:
        *pval = NULL;
        break;
    }
}