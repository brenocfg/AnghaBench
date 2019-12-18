#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509V3_CTX ;
struct TYPE_7__ {int /*<<< orphan*/  type_id; int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_4__* otherName; } ;
struct TYPE_6__ {TYPE_1__ d; } ;
typedef  TYPE_2__ GENERAL_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_generate_v3 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_txt2obj (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strndup (char const*,int) ; 
 TYPE_4__* OTHERNAME_new () ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int do_othername(GENERAL_NAME *gen, const char *value, X509V3_CTX *ctx)
{
    char *objtmp = NULL, *p;
    int objlen;

    if ((p = strchr(value, ';')) == NULL)
        return 0;
    if ((gen->d.otherName = OTHERNAME_new()) == NULL)
        return 0;
    /*
     * Free this up because we will overwrite it. no need to free type_id
     * because it is static
     */
    ASN1_TYPE_free(gen->d.otherName->value);
    if ((gen->d.otherName->value = ASN1_generate_v3(p + 1, ctx)) == NULL)
        return 0;
    objlen = p - value;
    objtmp = OPENSSL_strndup(value, objlen);
    if (objtmp == NULL)
        return 0;
    gen->d.otherName->type_id = OBJ_txt2obj(objtmp, 0);
    OPENSSL_free(objtmp);
    if (!gen->d.otherName->type_id)
        return 0;
    return 1;
}