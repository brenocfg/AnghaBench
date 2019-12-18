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
struct TYPE_3__ {int /*<<< orphan*/  extensions; int /*<<< orphan*/ * tsa; int /*<<< orphan*/ * nonce; scalar_t__ ordering; int /*<<< orphan*/ * accuracy; int /*<<< orphan*/  time; int /*<<< orphan*/ * serial; int /*<<< orphan*/  msg_imprint; int /*<<< orphan*/  policy_id; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ TS_TST_INFO ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ASN1_INTEGER_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CONF_VALUE ; 
 int STACK_OF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_ASN1_INTEGER_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_MSG_IMPRINT_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_OBJ_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_ext_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509V3_EXT_val_prn (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509V3_conf_free ; 
 int i2v_GENERAL_NAME (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nval ; 
 int /*<<< orphan*/  sk_CONF_VALUE_pop_free (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_ACCURACY_print_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int TS_TST_INFO_print_bio(BIO *bio, TS_TST_INFO *a)
{
    int v;

    if (a == NULL)
        return 0;

    v = ASN1_INTEGER_get(a->version);
    BIO_printf(bio, "Version: %d\n", v);

    BIO_printf(bio, "Policy OID: ");
    TS_OBJ_print_bio(bio, a->policy_id);

    TS_MSG_IMPRINT_print_bio(bio, a->msg_imprint);

    BIO_printf(bio, "Serial number: ");
    if (a->serial == NULL)
        BIO_printf(bio, "unspecified");
    else
        TS_ASN1_INTEGER_print_bio(bio, a->serial);
    BIO_write(bio, "\n", 1);

    BIO_printf(bio, "Time stamp: ");
    ASN1_GENERALIZEDTIME_print(bio, a->time);
    BIO_write(bio, "\n", 1);

    BIO_printf(bio, "Accuracy: ");
    if (a->accuracy == NULL)
        BIO_printf(bio, "unspecified");
    else
        ts_ACCURACY_print_bio(bio, a->accuracy);
    BIO_write(bio, "\n", 1);

    BIO_printf(bio, "Ordering: %s\n", a->ordering ? "yes" : "no");

    BIO_printf(bio, "Nonce: ");
    if (a->nonce == NULL)
        BIO_printf(bio, "unspecified");
    else
        TS_ASN1_INTEGER_print_bio(bio, a->nonce);
    BIO_write(bio, "\n", 1);

    BIO_printf(bio, "TSA: ");
    if (a->tsa == NULL)
        BIO_printf(bio, "unspecified");
    else {
        STACK_OF(CONF_VALUE) *nval;
        if ((nval = i2v_GENERAL_NAME(NULL, a->tsa, NULL)))
            X509V3_EXT_val_prn(bio, nval, 0, 0);
        sk_CONF_VALUE_pop_free(nval, X509V3_conf_free);
    }
    BIO_write(bio, "\n", 1);

    TS_ext_print_bio(bio, a->extensions);

    return 1;
}