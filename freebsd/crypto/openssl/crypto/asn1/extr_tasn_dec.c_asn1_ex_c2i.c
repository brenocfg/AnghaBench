#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int type; } ;
struct TYPE_20__ {scalar_t__ utype; TYPE_4__* funcs; } ;
struct TYPE_19__ {int (* prim_c2i ) (int /*<<< orphan*/ **,unsigned char const*,int,int,char*,TYPE_5__ const*) ;} ;
struct TYPE_18__ {int type; unsigned char* data; int length; } ;
struct TYPE_16__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * asn1_value; } ;
struct TYPE_17__ {int type; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_2__ ASN1_TYPE ;
typedef  TYPE_3__ ASN1_STRING ;
typedef  TYPE_4__ ASN1_PRIMITIVE_FUNCS ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  TYPE_5__ ASN1_ITEM ;
typedef  TYPE_6__ ASN1_INTEGER ;
typedef  unsigned char ASN1_BOOLEAN ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_EX_C2I ; 
 int /*<<< orphan*/  ASN1_R_BMPSTRING_IS_WRONG_LENGTH ; 
 int /*<<< orphan*/  ASN1_R_BOOLEAN_IS_WRONG_LENGTH ; 
 int /*<<< orphan*/  ASN1_R_NULL_IS_WRONG_LENGTH ; 
 int /*<<< orphan*/  ASN1_R_UNIVERSALSTRING_IS_WRONG_LENGTH ; 
 int /*<<< orphan*/  ASN1_STRING_free (TYPE_3__*) ; 
 int /*<<< orphan*/  ASN1_STRING_set (TYPE_3__*,unsigned char const*,int) ; 
 TYPE_3__* ASN1_STRING_type_new (int) ; 
 int /*<<< orphan*/  ASN1_TYPE_free (TYPE_2__*) ; 
 TYPE_2__* ASN1_TYPE_new () ; 
 int /*<<< orphan*/  ASN1_TYPE_set (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 scalar_t__ V_ASN1_ANY ; 
#define  V_ASN1_BIT_STRING 150 
#define  V_ASN1_BMPSTRING 149 
#define  V_ASN1_BOOLEAN 148 
#define  V_ASN1_ENUMERATED 147 
#define  V_ASN1_GENERALIZEDTIME 146 
#define  V_ASN1_GENERALSTRING 145 
#define  V_ASN1_GRAPHICSTRING 144 
#define  V_ASN1_IA5STRING 143 
#define  V_ASN1_INTEGER 142 
 int V_ASN1_NEG ; 
#define  V_ASN1_NULL 141 
#define  V_ASN1_NUMERICSTRING 140 
#define  V_ASN1_OBJECT 139 
#define  V_ASN1_OCTET_STRING 138 
#define  V_ASN1_OTHER 137 
#define  V_ASN1_PRINTABLESTRING 136 
#define  V_ASN1_SEQUENCE 135 
#define  V_ASN1_SET 134 
#define  V_ASN1_T61STRING 133 
#define  V_ASN1_UNIVERSALSTRING 132 
#define  V_ASN1_UTCTIME 131 
#define  V_ASN1_UTF8STRING 130 
#define  V_ASN1_VIDEOTEXSTRING 129 
#define  V_ASN1_VISIBLESTRING 128 
 int /*<<< orphan*/  c2i_ASN1_BIT_STRING (int /*<<< orphan*/ **,unsigned char const**,int) ; 
 int /*<<< orphan*/  c2i_ASN1_INTEGER (TYPE_6__**,unsigned char const**,int) ; 
 int /*<<< orphan*/  c2i_ASN1_OBJECT (int /*<<< orphan*/ **,unsigned char const**,int) ; 
 int stub1 (int /*<<< orphan*/ **,unsigned char const*,int,int,char*,TYPE_5__ const*) ; 

__attribute__((used)) static int asn1_ex_c2i(ASN1_VALUE **pval, const unsigned char *cont, int len,
                       int utype, char *free_cont, const ASN1_ITEM *it)
{
    ASN1_VALUE **opval = NULL;
    ASN1_STRING *stmp;
    ASN1_TYPE *typ = NULL;
    int ret = 0;
    const ASN1_PRIMITIVE_FUNCS *pf;
    ASN1_INTEGER **tint;
    pf = it->funcs;

    if (pf && pf->prim_c2i)
        return pf->prim_c2i(pval, cont, len, utype, free_cont, it);
    /* If ANY type clear type and set pointer to internal value */
    if (it->utype == V_ASN1_ANY) {
        if (!*pval) {
            typ = ASN1_TYPE_new();
            if (typ == NULL)
                goto err;
            *pval = (ASN1_VALUE *)typ;
        } else
            typ = (ASN1_TYPE *)*pval;

        if (utype != typ->type)
            ASN1_TYPE_set(typ, utype, NULL);
        opval = pval;
        pval = &typ->value.asn1_value;
    }
    switch (utype) {
    case V_ASN1_OBJECT:
        if (!c2i_ASN1_OBJECT((ASN1_OBJECT **)pval, &cont, len))
            goto err;
        break;

    case V_ASN1_NULL:
        if (len) {
            ASN1err(ASN1_F_ASN1_EX_C2I, ASN1_R_NULL_IS_WRONG_LENGTH);
            goto err;
        }
        *pval = (ASN1_VALUE *)1;
        break;

    case V_ASN1_BOOLEAN:
        if (len != 1) {
            ASN1err(ASN1_F_ASN1_EX_C2I, ASN1_R_BOOLEAN_IS_WRONG_LENGTH);
            goto err;
        } else {
            ASN1_BOOLEAN *tbool;
            tbool = (ASN1_BOOLEAN *)pval;
            *tbool = *cont;
        }
        break;

    case V_ASN1_BIT_STRING:
        if (!c2i_ASN1_BIT_STRING((ASN1_BIT_STRING **)pval, &cont, len))
            goto err;
        break;

    case V_ASN1_INTEGER:
    case V_ASN1_ENUMERATED:
        tint = (ASN1_INTEGER **)pval;
        if (!c2i_ASN1_INTEGER(tint, &cont, len))
            goto err;
        /* Fixup type to match the expected form */
        (*tint)->type = utype | ((*tint)->type & V_ASN1_NEG);
        break;

    case V_ASN1_OCTET_STRING:
    case V_ASN1_NUMERICSTRING:
    case V_ASN1_PRINTABLESTRING:
    case V_ASN1_T61STRING:
    case V_ASN1_VIDEOTEXSTRING:
    case V_ASN1_IA5STRING:
    case V_ASN1_UTCTIME:
    case V_ASN1_GENERALIZEDTIME:
    case V_ASN1_GRAPHICSTRING:
    case V_ASN1_VISIBLESTRING:
    case V_ASN1_GENERALSTRING:
    case V_ASN1_UNIVERSALSTRING:
    case V_ASN1_BMPSTRING:
    case V_ASN1_UTF8STRING:
    case V_ASN1_OTHER:
    case V_ASN1_SET:
    case V_ASN1_SEQUENCE:
    default:
        if (utype == V_ASN1_BMPSTRING && (len & 1)) {
            ASN1err(ASN1_F_ASN1_EX_C2I, ASN1_R_BMPSTRING_IS_WRONG_LENGTH);
            goto err;
        }
        if (utype == V_ASN1_UNIVERSALSTRING && (len & 3)) {
            ASN1err(ASN1_F_ASN1_EX_C2I,
                    ASN1_R_UNIVERSALSTRING_IS_WRONG_LENGTH);
            goto err;
        }
        /* All based on ASN1_STRING and handled the same */
        if (!*pval) {
            stmp = ASN1_STRING_type_new(utype);
            if (stmp == NULL) {
                ASN1err(ASN1_F_ASN1_EX_C2I, ERR_R_MALLOC_FAILURE);
                goto err;
            }
            *pval = (ASN1_VALUE *)stmp;
        } else {
            stmp = (ASN1_STRING *)*pval;
            stmp->type = utype;
        }
        /* If we've already allocated a buffer use it */
        if (*free_cont) {
            OPENSSL_free(stmp->data);
            stmp->data = (unsigned char *)cont; /* UGLY CAST! RL */
            stmp->length = len;
            *free_cont = 0;
        } else {
            if (!ASN1_STRING_set(stmp, cont, len)) {
                ASN1err(ASN1_F_ASN1_EX_C2I, ERR_R_MALLOC_FAILURE);
                ASN1_STRING_free(stmp);
                *pval = NULL;
                goto err;
            }
        }
        break;
    }
    /* If ASN1_ANY and NULL type fix up value */
    if (typ && (utype == V_ASN1_NULL))
        typ->value.ptr = NULL;

    ret = 1;
 err:
    if (!ret) {
        ASN1_TYPE_free(typ);
        if (opval)
            *opval = NULL;
    }
    return ret;
}