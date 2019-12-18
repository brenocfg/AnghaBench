#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pem_password_cb ;
struct TYPE_3__ {char* password; char* prompt_info; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_1__ PW_CB_DATA ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BN_GENCB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_GENCB_new () ; 
 int /*<<< orphan*/  BN_GENCB_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* BN_bn2dec (int /*<<< orphan*/  const*) ; 
 char* BN_bn2hex (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,unsigned long) ; 
 int DEFBITS ; 
 int DEFPRIMES ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORMAT_PEM ; 
 int OPENSSL_RSA_MAX_MODULUS_BITS ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_3 138 
#define  OPT_CIPHER 137 
#define  OPT_ENGINE 136 
#define  OPT_EOF 135 
#define  OPT_ERR 134 
#define  OPT_F4 133 
#define  OPT_HELP 132 
#define  OPT_OUT 131 
#define  OPT_PASSOUT 130 
#define  OPT_PRIMES 129 
#define  OPT_R_CASES 128 
 int /*<<< orphan*/  PEM_write_bio_RSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 unsigned long RSA_F4 ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_generate_multi_prime_key (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/ * RSA_new_method (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  app_passwd (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  genrsa_cb ; 
 int /*<<< orphan*/  genrsa_options ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_int (char*,int*) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_rand (int) ; 
 char** opt_rest () ; 
 int /*<<< orphan*/  opt_unknown () ; 
 scalar_t__ password_callback ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int genrsa_main(int argc, char **argv)
{
    BN_GENCB *cb = BN_GENCB_new();
    PW_CB_DATA cb_data;
    ENGINE *eng = NULL;
    BIGNUM *bn = BN_new();
    BIO *out = NULL;
    const BIGNUM *e;
    RSA *rsa = NULL;
    const EVP_CIPHER *enc = NULL;
    int ret = 1, num = DEFBITS, private = 0, primes = DEFPRIMES;
    unsigned long f4 = RSA_F4;
    char *outfile = NULL, *passoutarg = NULL, *passout = NULL;
    char *prog, *hexe, *dece;
    OPTION_CHOICE o;

    if (bn == NULL || cb == NULL)
        goto end;

    BN_GENCB_set(cb, genrsa_cb, bio_err);

    prog = opt_init(argc, argv, genrsa_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            ret = 0;
            opt_help(genrsa_options);
            goto end;
        case OPT_3:
            f4 = 3;
            break;
        case OPT_F4:
            f4 = RSA_F4;
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_ENGINE:
            eng = setup_engine(opt_arg(), 0);
            break;
        case OPT_R_CASES:
            if (!opt_rand(o))
                goto end;
            break;
        case OPT_PASSOUT:
            passoutarg = opt_arg();
            break;
        case OPT_CIPHER:
            if (!opt_cipher(opt_unknown(), &enc))
                goto end;
            break;
        case OPT_PRIMES:
            if (!opt_int(opt_arg(), &primes))
                goto end;
            break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();

    if (argc == 1) {
        if (!opt_int(argv[0], &num) || num <= 0)
            goto end;
        if (num > OPENSSL_RSA_MAX_MODULUS_BITS)
            BIO_printf(bio_err,
                       "Warning: It is not recommended to use more than %d bit for RSA keys.\n"
                       "         Your key size is %d! Larger key size may behave not as expected.\n",
                       OPENSSL_RSA_MAX_MODULUS_BITS, num);
    } else if (argc > 0) {
        BIO_printf(bio_err, "Extra arguments given.\n");
        goto opthelp;
    }

    private = 1;
    if (!app_passwd(NULL, passoutarg, NULL, &passout)) {
        BIO_printf(bio_err, "Error getting password\n");
        goto end;
    }

    out = bio_open_owner(outfile, FORMAT_PEM, private);
    if (out == NULL)
        goto end;

    BIO_printf(bio_err, "Generating RSA private key, %d bit long modulus (%d primes)\n",
               num, primes);
    rsa = eng ? RSA_new_method(eng) : RSA_new();
    if (rsa == NULL)
        goto end;

    if (!BN_set_word(bn, f4)
        || !RSA_generate_multi_prime_key(rsa, num, primes, bn, cb))
        goto end;

    RSA_get0_key(rsa, NULL, &e, NULL);
    hexe = BN_bn2hex(e);
    dece = BN_bn2dec(e);
    if (hexe && dece) {
        BIO_printf(bio_err, "e is %s (0x%s)\n", dece, hexe);
    }
    OPENSSL_free(hexe);
    OPENSSL_free(dece);
    cb_data.password = passout;
    cb_data.prompt_info = outfile;
    assert(private);
    if (!PEM_write_bio_RSAPrivateKey(out, rsa, enc, NULL, 0,
                                     (pem_password_cb *)password_callback,
                                     &cb_data))
        goto end;

    ret = 0;
 end:
    BN_free(bn);
    BN_GENCB_free(cb);
    RSA_free(rsa);
    BIO_free_all(out);
    release_engine(eng);
    OPENSSL_free(passout);
    if (ret != 0)
        ERR_print_errors(bio_err);
    return ret;
}