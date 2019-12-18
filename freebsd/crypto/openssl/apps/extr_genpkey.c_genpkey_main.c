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
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_mode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_CIPH_CCM_MODE ; 
 int /*<<< orphan*/  EVP_CIPH_GCM_MODE ; 
 int /*<<< orphan*/  EVP_CIPH_OCB_MODE ; 
 int /*<<< orphan*/  EVP_CIPH_XTS_MODE ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_set_app_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_set_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ EVP_PKEY_paramgen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int EVP_PKEY_print_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_print_private (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_PEM ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_ALGORITHM 140 
#define  OPT_CIPHER 139 
#define  OPT_ENGINE 138 
#define  OPT_EOF 137 
#define  OPT_ERR 136 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
#define  OPT_GENPARAM 135 
#define  OPT_HELP 134 
#define  OPT_OUT 133 
#define  OPT_OUTFORM 132 
#define  OPT_PARAMFILE 131 
#define  OPT_PASS 130 
#define  OPT_PKEYOPT 129 
#define  OPT_TEXT 128 
 int PEM_write_bio_Parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PEM_write_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  app_passwd (char*,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int,int) ; 
 int /*<<< orphan*/  genpkey_cb ; 
 int /*<<< orphan*/  genpkey_options ; 
 int i2d_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_gen_str (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_keygen_file (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  opt_format (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_unknown () ; 
 int /*<<< orphan*/  pkey_ctrl_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int genpkey_main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL;
    ENGINE *e = NULL;
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    char *outfile = NULL, *passarg = NULL, *pass = NULL, *prog;
    const EVP_CIPHER *cipher = NULL;
    OPTION_CHOICE o;
    int outformat = FORMAT_PEM, text = 0, ret = 1, rv, do_param = 0;
    int private = 0;

    prog = opt_init(argc, argv, genpkey_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            ret = 0;
            opt_help(genpkey_options);
            goto end;
        case OPT_OUTFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &outformat))
                goto opthelp;
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_PASS:
            passarg = opt_arg();
            break;
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        case OPT_PARAMFILE:
            if (do_param == 1)
                goto opthelp;
            if (!init_keygen_file(&ctx, opt_arg(), e))
                goto end;
            break;
        case OPT_ALGORITHM:
            if (!init_gen_str(&ctx, opt_arg(), e, do_param))
                goto end;
            break;
        case OPT_PKEYOPT:
            if (ctx == NULL) {
                BIO_printf(bio_err, "%s: No keytype specified.\n", prog);
                goto opthelp;
            }
            if (pkey_ctrl_string(ctx, opt_arg()) <= 0) {
                BIO_printf(bio_err,
                           "%s: Error setting %s parameter:\n",
                           prog, opt_arg());
                ERR_print_errors(bio_err);
                goto end;
            }
            break;
        case OPT_GENPARAM:
            if (ctx != NULL)
                goto opthelp;
            do_param = 1;
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_CIPHER:
            if (!opt_cipher(opt_unknown(), &cipher)
                || do_param == 1)
                goto opthelp;
            if (EVP_CIPHER_mode(cipher) == EVP_CIPH_GCM_MODE ||
                EVP_CIPHER_mode(cipher) == EVP_CIPH_CCM_MODE ||
                EVP_CIPHER_mode(cipher) == EVP_CIPH_XTS_MODE ||
                EVP_CIPHER_mode(cipher) == EVP_CIPH_OCB_MODE) {
                BIO_printf(bio_err, "%s: cipher mode not supported\n", prog);
                goto end;
            }
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    private = do_param ? 0 : 1;

    if (ctx == NULL)
        goto opthelp;

    if (!app_passwd(passarg, NULL, &pass, NULL)) {
        BIO_puts(bio_err, "Error getting password\n");
        goto end;
    }

    out = bio_open_owner(outfile, outformat, private);
    if (out == NULL)
        goto end;

    EVP_PKEY_CTX_set_cb(ctx, genpkey_cb);
    EVP_PKEY_CTX_set_app_data(ctx, bio_err);

    if (do_param) {
        if (EVP_PKEY_paramgen(ctx, &pkey) <= 0) {
            BIO_puts(bio_err, "Error generating parameters\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    } else {
        if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
            BIO_puts(bio_err, "Error generating key\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }

    if (do_param) {
        rv = PEM_write_bio_Parameters(out, pkey);
    } else if (outformat == FORMAT_PEM) {
        assert(private);
        rv = PEM_write_bio_PrivateKey(out, pkey, cipher, NULL, 0, NULL, pass);
    } else if (outformat == FORMAT_ASN1) {
        assert(private);
        rv = i2d_PrivateKey_bio(out, pkey);
    } else {
        BIO_printf(bio_err, "Bad format specified for key\n");
        goto end;
    }

    if (rv <= 0) {
        BIO_puts(bio_err, "Error writing key\n");
        ERR_print_errors(bio_err);
    }

    if (text) {
        if (do_param)
            rv = EVP_PKEY_print_params(out, pkey, 0, NULL);
        else
            rv = EVP_PKEY_print_private(out, pkey, 0, NULL);

        if (rv <= 0) {
            BIO_puts(bio_err, "Error printing key\n");
            ERR_print_errors(bio_err);
        }
    }

    ret = 0;

 end:
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    BIO_free_all(out);
    BIO_free(in);
    release_engine(e);
    OPENSSL_free(pass);
    return ret;
}