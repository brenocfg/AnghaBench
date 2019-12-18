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
typedef  int /*<<< orphan*/  oidstr ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  OBJ_obj2txt (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int STACK_OF (int /*<<< orphan*/ ) ; 
 unsigned char* X509_alias_get0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_reject_objects (int /*<<< orphan*/ *) ; 
 int X509_get0_trust_objects (int /*<<< orphan*/ *) ; 
 unsigned char* X509_keyid_get0 (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ X509_trusted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * reject ; 
 int sk_ASN1_OBJECT_num (int) ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_value (int,int) ; 
 int trust ; 

int X509_aux_print(BIO *out, X509 *x, int indent)
{
    char oidstr[80], first;
    STACK_OF(ASN1_OBJECT) *trust, *reject;
    const unsigned char *alias, *keyid;
    int keyidlen;
    int i;
    if (X509_trusted(x) == 0)
        return 1;
    trust = X509_get0_trust_objects(x);
    reject = X509_get0_reject_objects(x);
    if (trust) {
        first = 1;
        BIO_printf(out, "%*sTrusted Uses:\n%*s", indent, "", indent + 2, "");
        for (i = 0; i < sk_ASN1_OBJECT_num(trust); i++) {
            if (!first)
                BIO_puts(out, ", ");
            else
                first = 0;
            OBJ_obj2txt(oidstr, sizeof(oidstr),
                        sk_ASN1_OBJECT_value(trust, i), 0);
            BIO_puts(out, oidstr);
        }
        BIO_puts(out, "\n");
    } else
        BIO_printf(out, "%*sNo Trusted Uses.\n", indent, "");
    if (reject) {
        first = 1;
        BIO_printf(out, "%*sRejected Uses:\n%*s", indent, "", indent + 2, "");
        for (i = 0; i < sk_ASN1_OBJECT_num(reject); i++) {
            if (!first)
                BIO_puts(out, ", ");
            else
                first = 0;
            OBJ_obj2txt(oidstr, sizeof(oidstr),
                        sk_ASN1_OBJECT_value(reject, i), 0);
            BIO_puts(out, oidstr);
        }
        BIO_puts(out, "\n");
    } else
        BIO_printf(out, "%*sNo Rejected Uses.\n", indent, "");
    alias = X509_alias_get0(x, NULL);
    if (alias)
        BIO_printf(out, "%*sAlias: %s\n", indent, "", alias);
    keyid = X509_keyid_get0(x, &keyidlen);
    if (keyid) {
        BIO_printf(out, "%*sKey Id: ", indent, "");
        for (i = 0; i < keyidlen; i++)
            BIO_printf(out, "%s%02X", i ? ":" : "", keyid[i]);
        BIO_write(out, "\n", 1);
    }
    return 1;
}