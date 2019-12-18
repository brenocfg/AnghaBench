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
struct test_crypto_options {int /*<<< orphan*/  pass_strings; } ;
typedef  int /*<<< orphan*/  hx509_verify_ctx ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int hx509_certs_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_verify_attach_anchors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hx509_verify_init_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_one_cert ; 

int
test_crypto(struct test_crypto_options *opt, int argc, char ** argv)
{
    hx509_verify_ctx vctx;
    hx509_certs certs;
    hx509_lock lock;
    int i, ret;

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    ret = hx509_certs_init(context, "MEMORY:test-crypto", 0, NULL, &certs);
    if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");

    for (i = 0; i < argc; i++) {
	ret = hx509_certs_append(context, certs, lock, argv[i]);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_certs_append");
    }

    ret = hx509_verify_init_ctx(context, &vctx);
    if (ret)
	hx509_err(context, 1, ret, "hx509_verify_init_ctx");

    hx509_verify_attach_anchors(vctx, certs);

    ret = hx509_certs_iter_f(context, certs, test_one_cert, vctx);
    if (ret)
	hx509_err(context, 1, ret, "hx509_cert_iter");

    hx509_certs_free(&certs);

    return 0;
}