#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
typedef  int /*<<< orphan*/  X509V3_CTX ;
struct TYPE_9__ {int /*<<< orphan*/ * ia5; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * rid; } ;
struct TYPE_10__ {int type; TYPE_1__ d; } ;
typedef  TYPE_2__ GENERAL_NAME ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_IA5STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/  GENERAL_NAME_free (TYPE_2__*) ; 
 TYPE_2__* GENERAL_NAME_new () ; 
#define  GEN_DIRNAME 134 
#define  GEN_DNS 133 
#define  GEN_EMAIL 132 
#define  GEN_IPADD 131 
#define  GEN_OTHERNAME 130 
#define  GEN_RID 129 
#define  GEN_URI 128 
 int /*<<< orphan*/ * OBJ_txt2obj (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509V3_F_A2I_GENERAL_NAME ; 
 int /*<<< orphan*/  X509V3_R_BAD_IP_ADDRESS ; 
 int /*<<< orphan*/  X509V3_R_BAD_OBJECT ; 
 int /*<<< orphan*/  X509V3_R_DIRNAME_ERROR ; 
 int /*<<< orphan*/  X509V3_R_MISSING_VALUE ; 
 int /*<<< orphan*/  X509V3_R_OTHERNAME_ERROR ; 
 int /*<<< orphan*/  X509V3_R_UNSUPPORTED_TYPE ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * a2i_IPADDRESS (char const*) ; 
 int /*<<< orphan*/ * a2i_IPADDRESS_NC (char const*) ; 
 int /*<<< orphan*/  do_dirname (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_othername (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

GENERAL_NAME *a2i_GENERAL_NAME(GENERAL_NAME *out,
                               const X509V3_EXT_METHOD *method,
                               X509V3_CTX *ctx, int gen_type, const char *value,
                               int is_nc)
{
    char is_string = 0;
    GENERAL_NAME *gen = NULL;

    if (!value) {
        X509V3err(X509V3_F_A2I_GENERAL_NAME, X509V3_R_MISSING_VALUE);
        return NULL;
    }

    if (out)
        gen = out;
    else {
        gen = GENERAL_NAME_new();
        if (gen == NULL) {
            X509V3err(X509V3_F_A2I_GENERAL_NAME, ERR_R_MALLOC_FAILURE);
            return NULL;
        }
    }

    switch (gen_type) {
    case GEN_URI:
    case GEN_EMAIL:
    case GEN_DNS:
        is_string = 1;
        break;

    case GEN_RID:
        {
            ASN1_OBJECT *obj;
            if ((obj = OBJ_txt2obj(value, 0)) == NULL) {
                X509V3err(X509V3_F_A2I_GENERAL_NAME, X509V3_R_BAD_OBJECT);
                ERR_add_error_data(2, "value=", value);
                goto err;
            }
            gen->d.rid = obj;
        }
        break;

    case GEN_IPADD:
        if (is_nc)
            gen->d.ip = a2i_IPADDRESS_NC(value);
        else
            gen->d.ip = a2i_IPADDRESS(value);
        if (gen->d.ip == NULL) {
            X509V3err(X509V3_F_A2I_GENERAL_NAME, X509V3_R_BAD_IP_ADDRESS);
            ERR_add_error_data(2, "value=", value);
            goto err;
        }
        break;

    case GEN_DIRNAME:
        if (!do_dirname(gen, value, ctx)) {
            X509V3err(X509V3_F_A2I_GENERAL_NAME, X509V3_R_DIRNAME_ERROR);
            goto err;
        }
        break;

    case GEN_OTHERNAME:
        if (!do_othername(gen, value, ctx)) {
            X509V3err(X509V3_F_A2I_GENERAL_NAME, X509V3_R_OTHERNAME_ERROR);
            goto err;
        }
        break;
    default:
        X509V3err(X509V3_F_A2I_GENERAL_NAME, X509V3_R_UNSUPPORTED_TYPE);
        goto err;
    }

    if (is_string) {
        if ((gen->d.ia5 = ASN1_IA5STRING_new()) == NULL ||
            !ASN1_STRING_set(gen->d.ia5, (unsigned char *)value,
                             strlen(value))) {
            X509V3err(X509V3_F_A2I_GENERAL_NAME, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }

    gen->type = gen_type;

    return gen;

 err:
    if (!out)
        GENERAL_NAME_free(gen);
    return NULL;
}