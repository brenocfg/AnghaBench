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
struct TYPE_6__ {scalar_t__ num_strings; } ;
struct crypto_select_options {TYPE_2__ peer_cmstype_strings; scalar_t__ type_string; } ;
typedef  int /*<<< orphan*/ * hx509_peer_info ;
struct TYPE_5__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ AlgorithmIdentifier ;

/* Variables and functions */
 int HX509_SELECT_DIGEST ; 
 int HX509_SELECT_PUBLIC_SIG ; 
 int HX509_SELECT_SECRET_ENC ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  der_print_heim_oid (int /*<<< orphan*/ *,char,char**) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_AlgorithmIdentifier (TYPE_1__*) ; 
 int hx509_crypto_select (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_peer_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peer_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

int
crypto_select(struct crypto_select_options *opt, int argc, char **argv)
{
    hx509_peer_info peer = NULL;
    AlgorithmIdentifier selected;
    int ret, type = HX509_SELECT_DIGEST;
    char *s;

    if (opt->type_string) {
	if (strcmp(opt->type_string, "digest") == 0)
	    type = HX509_SELECT_DIGEST;
	else if (strcmp(opt->type_string, "public-sig") == 0)
	    type = HX509_SELECT_PUBLIC_SIG;
	else if (strcmp(opt->type_string, "secret") == 0)
	    type = HX509_SELECT_SECRET_ENC;
	else
	    errx(1, "unknown type: %s", opt->type_string);
    }

    if (opt->peer_cmstype_strings.num_strings)
	peer_strings(context, &peer, &opt->peer_cmstype_strings);

    ret = hx509_crypto_select(context, type, NULL, peer, &selected);
    if (ret)
	errx(1, "hx509_crypto_available");

    der_print_heim_oid (&selected.algorithm, '.', &s);
    printf("%s\n", s);
    free(s);
    free_AlgorithmIdentifier(&selected);

    hx509_peer_info_free(peer);

    return 0;
}