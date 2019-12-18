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
struct validate_options {int /*<<< orphan*/  pass_strings; } ;
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_VALIDATE_F_VALIDATE ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_print_stdout ; 
 int /*<<< orphan*/  hx509_validate_ctx_add_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_validate_ctx_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_validate_ctx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_validate_ctx_set_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  validate_f ; 

int
pcert_validate(struct validate_options *opt, int argc, char **argv)
{
    hx509_validate_ctx ctx;
    hx509_certs certs;
    hx509_lock lock;

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    hx509_validate_ctx_init(context, &ctx);
    hx509_validate_ctx_set_print(ctx, hx509_print_stdout, stdout);
    hx509_validate_ctx_add_flags(ctx, HX509_VALIDATE_F_VALIDATE);

    while(argc--) {
	int ret;
	ret = hx509_certs_init(context, argv[0], 0, lock, &certs);
	if (ret)
	    errx(1, "hx509_certs_init: %d", ret);
	hx509_certs_iter_f(context, certs, validate_f, ctx);
	hx509_certs_free(&certs);
	argv++;
    }
    hx509_validate_ctx_free(ctx);

    hx509_lock_free(lock);

    return 0;
}