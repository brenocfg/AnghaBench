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
struct crypto_available_options {scalar_t__ type_string; } ;
struct TYPE_4__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ AlgorithmIdentifier ;

/* Variables and functions */
 int HX509_SELECT_ALL ; 
 int HX509_SELECT_DIGEST ; 
 int HX509_SELECT_PUBLIC_SIG ; 
 int HX509_SELECT_SECRET_ENC ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  der_print_heim_oid (int /*<<< orphan*/ *,char,char**) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hx509_crypto_available (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__**,unsigned int*) ; 
 int /*<<< orphan*/  hx509_crypto_free_algs (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

int
crypto_available(struct crypto_available_options *opt, int argc, char **argv)
{
    AlgorithmIdentifier *val;
    unsigned int len, i;
    int ret, type = HX509_SELECT_ALL;

    if (opt->type_string) {
	if (strcmp(opt->type_string, "all") == 0)
	    type = HX509_SELECT_ALL;
	else if (strcmp(opt->type_string, "digest") == 0)
	    type = HX509_SELECT_DIGEST;
	else if (strcmp(opt->type_string, "public-sig") == 0)
	    type = HX509_SELECT_PUBLIC_SIG;
	else if (strcmp(opt->type_string, "secret") == 0)
	    type = HX509_SELECT_SECRET_ENC;
	else
	    errx(1, "unknown type: %s", opt->type_string);
    }

    ret = hx509_crypto_available(context, type, NULL, &val, &len);
    if (ret)
	errx(1, "hx509_crypto_available");

    for (i = 0; i < len; i++) {
	char *s;
	der_print_heim_oid (&val[i].algorithm, '.', &s);
	printf("%s\n", s);
	free(s);
    }

    hx509_crypto_free_algs(val, len);

    return 0;
}