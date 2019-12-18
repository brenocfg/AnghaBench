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
struct TYPE_5__ {int /*<<< orphan*/  rid; int /*<<< orphan*/  ip; int /*<<< orphan*/  dirn; int /*<<< orphan*/  ia5; int /*<<< orphan*/  otherName; int /*<<< orphan*/  other; } ;
struct TYPE_6__ {int type; TYPE_1__ d; } ;
typedef  TYPE_2__ GENERAL_NAME ;

/* Variables and functions */
 int ASN1_OCTET_STRING_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ASN1_STRING_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ASN1_TYPE_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  GEN_DIRNAME 136 
#define  GEN_DNS 135 
#define  GEN_EDIPARTY 134 
#define  GEN_EMAIL 133 
#define  GEN_IPADD 132 
#define  GEN_OTHERNAME 131 
#define  GEN_RID 130 
#define  GEN_URI 129 
#define  GEN_X400 128 
 int OBJ_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OTHERNAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int GENERAL_NAME_cmp(GENERAL_NAME *a, GENERAL_NAME *b)
{
    int result = -1;

    if (!a || !b || a->type != b->type)
        return -1;
    switch (a->type) {
    case GEN_X400:
    case GEN_EDIPARTY:
        result = ASN1_TYPE_cmp(a->d.other, b->d.other);
        break;

    case GEN_OTHERNAME:
        result = OTHERNAME_cmp(a->d.otherName, b->d.otherName);
        break;

    case GEN_EMAIL:
    case GEN_DNS:
    case GEN_URI:
        result = ASN1_STRING_cmp(a->d.ia5, b->d.ia5);
        break;

    case GEN_DIRNAME:
        result = X509_NAME_cmp(a->d.dirn, b->d.dirn);
        break;

    case GEN_IPADD:
        result = ASN1_OCTET_STRING_cmp(a->d.ip, b->d.ip);
        break;

    case GEN_RID:
        result = OBJ_cmp(a->d.rid, b->d.rid);
        break;
    }
    return result;
}