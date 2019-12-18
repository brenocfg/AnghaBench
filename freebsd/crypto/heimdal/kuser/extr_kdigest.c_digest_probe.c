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
struct digest_probe_options {int /*<<< orphan*/ * realm_string; } ;
typedef  int /*<<< orphan*/ * krb5_realm ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  id ; 
 scalar_t__ krb5_digest_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

int
digest_probe(struct digest_probe_options *opt,
	     int argc, char ** argv)
{
    krb5_error_code ret;
    krb5_realm realm;
    unsigned flags;

    realm = opt->realm_string;

    if (realm == NULL)
	errx(1, "realm missing");

    ret = krb5_digest_probe(context, realm, id, &flags);
    if (ret)
	krb5_err(context, 1, ret, "digest_probe");

    printf("flags: %u\n", flags);

    return 0;
}