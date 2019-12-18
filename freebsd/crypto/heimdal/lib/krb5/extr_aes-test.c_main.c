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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int iov_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 int krb_enc_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int random_to_key (int /*<<< orphan*/ ) ; 
 int string_to_key_test (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

int
main(int argc, char **argv)
{
    krb5_error_code ret;
    krb5_context context;
    int val = 0;

    ret = krb5_init_context (&context);
    if (ret)
	errx (1, "krb5_init_context failed: %d", ret);

    val |= string_to_key_test(context);

    val |= krb_enc_test(context);
    val |= random_to_key(context);
    val |= iov_test(context);

    if (verbose && val == 0)
	printf("all ok\n");
    if (val)
	printf("tests failed\n");

    krb5_free_context(context);

    return val;
}