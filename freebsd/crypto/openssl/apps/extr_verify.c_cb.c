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
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ X509_STORE_CTX_get0_parent_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_current_cert (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_get_error_depth (int /*<<< orphan*/ *) ; 
#define  X509_V_ERR_CERT_HAS_EXPIRED 137 
#define  X509_V_ERR_CRL_HAS_EXPIRED 136 
#define  X509_V_ERR_CRL_NOT_YET_VALID 135 
#define  X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT 134 
#define  X509_V_ERR_INVALID_CA 133 
#define  X509_V_ERR_INVALID_NON_CA 132 
#define  X509_V_ERR_INVALID_PURPOSE 131 
#define  X509_V_ERR_NO_EXPLICIT_POLICY 130 
#define  X509_V_ERR_PATH_LENGTH_EXCEEDED 129 
#define  X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION 128 
 int X509_V_OK ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_verify_cert_error_string (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  get_nameopt () ; 
 int /*<<< orphan*/  policies_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_verbose ; 

__attribute__((used)) static int cb(int ok, X509_STORE_CTX *ctx)
{
    int cert_error = X509_STORE_CTX_get_error(ctx);
    X509 *current_cert = X509_STORE_CTX_get_current_cert(ctx);

    if (!ok) {
        if (current_cert != NULL) {
            X509_NAME_print_ex(bio_err,
                            X509_get_subject_name(current_cert),
                            0, get_nameopt());
            BIO_printf(bio_err, "\n");
        }
        BIO_printf(bio_err, "%serror %d at %d depth lookup: %s\n",
               X509_STORE_CTX_get0_parent_ctx(ctx) ? "[CRL path] " : "",
               cert_error,
               X509_STORE_CTX_get_error_depth(ctx),
               X509_verify_cert_error_string(cert_error));

        /*
         * Pretend that some errors are ok, so they don't stop further
         * processing of the certificate chain.  Setting ok = 1 does this.
         * After X509_verify_cert() is done, we verify that there were
         * no actual errors, even if the returned value was positive.
         */
        switch (cert_error) {
        case X509_V_ERR_NO_EXPLICIT_POLICY:
            policies_print(ctx);
            /* fall thru */
        case X509_V_ERR_CERT_HAS_EXPIRED:
            /* Continue even if the leaf is a self signed cert */
        case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
            /* Continue after extension errors too */
        case X509_V_ERR_INVALID_CA:
        case X509_V_ERR_INVALID_NON_CA:
        case X509_V_ERR_PATH_LENGTH_EXCEEDED:
        case X509_V_ERR_INVALID_PURPOSE:
        case X509_V_ERR_CRL_HAS_EXPIRED:
        case X509_V_ERR_CRL_NOT_YET_VALID:
        case X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION:
            ok = 1;
        }

        return ok;

    }
    if (cert_error == X509_V_OK && ok == 2)
        policies_print(ctx);
    if (!v_verbose)
        ERR_clear_error();
    return ok;
}