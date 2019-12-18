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
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_VALIDATE_F_VALIDATE ; 
 int /*<<< orphan*/  HX509_VALIDATE_F_VERBOSE ; 
 scalar_t__ _hx509_cert_private_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* hx509_cert_get_friendly_name (int /*<<< orphan*/ ) ; 
 int hx509_print_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_print_stdout ; 
 int /*<<< orphan*/  hx509_validate_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_validate_ctx_add_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_validate_ctx_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_validate_ctx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_validate_ctx_set_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
print_certificate(hx509_context hxcontext, hx509_cert cert, int verbose)
{
    const char *fn;
    int ret;

    fn = hx509_cert_get_friendly_name(cert);
    if (fn)
	printf("    friendly name: %s\n", fn);
    printf("    private key: %s\n",
	   _hx509_cert_private_key(cert) ? "yes" : "no");

    ret = hx509_print_cert(hxcontext, cert, NULL);
    if (ret)
	errx(1, "failed to print cert");

    if (verbose) {
	hx509_validate_ctx vctx;

	hx509_validate_ctx_init(hxcontext, &vctx);
	hx509_validate_ctx_set_print(vctx, hx509_print_stdout, stdout);
	hx509_validate_ctx_add_flags(vctx, HX509_VALIDATE_F_VALIDATE);
	hx509_validate_ctx_add_flags(vctx, HX509_VALIDATE_F_VERBOSE);

	hx509_validate_cert(hxcontext, vctx, cert);

	hx509_validate_ctx_free(vctx);
    }
}