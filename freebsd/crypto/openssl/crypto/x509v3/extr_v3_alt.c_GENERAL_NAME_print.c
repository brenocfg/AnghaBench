#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rid; TYPE_1__* ip; int /*<<< orphan*/  dirn; int /*<<< orphan*/  ia5; } ;
struct TYPE_7__ {int type; TYPE_2__ d; } ;
struct TYPE_5__ {unsigned char* data; int length; } ;
typedef  TYPE_3__ GENERAL_NAME ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
#define  GEN_DIRNAME 136 
#define  GEN_DNS 135 
#define  GEN_EDIPARTY 134 
#define  GEN_EMAIL 133 
#define  GEN_IPADD 132 
#define  GEN_OTHERNAME 131 
#define  GEN_RID 130 
#define  GEN_URI 129 
#define  GEN_X400 128 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XN_FLAG_ONELINE ; 
 int /*<<< orphan*/  i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int GENERAL_NAME_print(BIO *out, GENERAL_NAME *gen)
{
    unsigned char *p;
    int i;
    switch (gen->type) {
    case GEN_OTHERNAME:
        BIO_printf(out, "othername:<unsupported>");
        break;

    case GEN_X400:
        BIO_printf(out, "X400Name:<unsupported>");
        break;

    case GEN_EDIPARTY:
        /* Maybe fix this: it is supported now */
        BIO_printf(out, "EdiPartyName:<unsupported>");
        break;

    case GEN_EMAIL:
        BIO_printf(out, "email:");
        ASN1_STRING_print(out, gen->d.ia5);
        break;

    case GEN_DNS:
        BIO_printf(out, "DNS:");
        ASN1_STRING_print(out, gen->d.ia5);
        break;

    case GEN_URI:
        BIO_printf(out, "URI:");
        ASN1_STRING_print(out, gen->d.ia5);
        break;

    case GEN_DIRNAME:
        BIO_printf(out, "DirName:");
        X509_NAME_print_ex(out, gen->d.dirn, 0, XN_FLAG_ONELINE);
        break;

    case GEN_IPADD:
        p = gen->d.ip->data;
        if (gen->d.ip->length == 4)
            BIO_printf(out, "IP Address:%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
        else if (gen->d.ip->length == 16) {
            BIO_printf(out, "IP Address");
            for (i = 0; i < 8; i++) {
                BIO_printf(out, ":%X", p[0] << 8 | p[1]);
                p += 2;
            }
            BIO_puts(out, "\n");
        } else {
            BIO_printf(out, "IP Address:<invalid>");
            break;
        }
        break;

    case GEN_RID:
        BIO_printf(out, "Registered ID:");
        i2a_ASN1_OBJECT(out, gen->d.rid);
        break;
    }
    return 1;
}