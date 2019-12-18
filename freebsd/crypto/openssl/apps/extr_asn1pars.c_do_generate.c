#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  CONF ;
typedef  TYPE_1__ BUF_MEM ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_generate_nconf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  BUF_MEM_grow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * app_load_config (char const*) ; 
 int /*<<< orphan*/  bio_err ; 
 int i2d_ASN1_TYPE (int /*<<< orphan*/ *,unsigned char**) ; 

__attribute__((used)) static int do_generate(char *genstr, const char *genconf, BUF_MEM *buf)
{
    CONF *cnf = NULL;
    int len;
    unsigned char *p;
    ASN1_TYPE *atyp = NULL;

    if (genconf != NULL) {
        if ((cnf = app_load_config(genconf)) == NULL)
            goto err;
        if (genstr == NULL)
            genstr = NCONF_get_string(cnf, "default", "asn1");
        if (genstr == NULL) {
            BIO_printf(bio_err, "Can't find 'asn1' in '%s'\n", genconf);
            goto err;
        }
    }

    atyp = ASN1_generate_nconf(genstr, cnf);
    NCONF_free(cnf);
    cnf = NULL;

    if (atyp == NULL)
        return -1;

    len = i2d_ASN1_TYPE(atyp, NULL);

    if (len <= 0)
        goto err;

    if (!BUF_MEM_grow(buf, len))
        goto err;

    p = (unsigned char *)buf->data;

    i2d_ASN1_TYPE(atyp, &p);

    ASN1_TYPE_free(atyp);
    return len;

 err:
    NCONF_free(cnf);
    ASN1_TYPE_free(atyp);
    return -1;
}