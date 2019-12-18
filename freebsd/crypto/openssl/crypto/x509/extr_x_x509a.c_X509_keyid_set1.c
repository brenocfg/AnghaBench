#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * keyid; } ;
typedef  TYPE_2__ X509_CERT_AUX ;
struct TYPE_9__ {TYPE_1__* aux; } ;
typedef  TYPE_3__ X509 ;
struct TYPE_7__ {int /*<<< orphan*/ * keyid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int ASN1_STRING_set (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 TYPE_2__* aux_get (TYPE_3__*) ; 

int X509_keyid_set1(X509 *x, const unsigned char *id, int len)
{
    X509_CERT_AUX *aux;
    if (!id) {
        if (!x || !x->aux || !x->aux->keyid)
            return 1;
        ASN1_OCTET_STRING_free(x->aux->keyid);
        x->aux->keyid = NULL;
        return 1;
    }
    if ((aux = aux_get(x)) == NULL)
        return 0;
    if (aux->keyid == NULL
        && (aux->keyid = ASN1_OCTET_STRING_new()) == NULL)
        return 0;
    return ASN1_STRING_set(aux->keyid, id, len);
}