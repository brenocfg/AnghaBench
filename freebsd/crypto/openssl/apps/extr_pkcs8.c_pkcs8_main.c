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
typedef  int /*<<< orphan*/  pass ;
typedef  int /*<<< orphan*/  X509_SIG ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int APP_PASS_LEN ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PBE_TYPE_PRF ; 
 int /*<<< orphan*/  EVP_PBE_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_PKCS82PKEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY2PKCS8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_aes_256_cbc () ; 
 scalar_t__ EVP_read_pw_string (char*,int,char*,int) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_PEM ; 
 int NID_undef ; 
 int OBJ_txt2nid (char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_ENGINE 150 
#define  OPT_EOF 149 
#define  OPT_ERR 148 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
#define  OPT_HELP 147 
#define  OPT_IN 146 
#define  OPT_INFORM 145 
#define  OPT_ITER 144 
#define  OPT_NOCRYPT 143 
#define  OPT_NOITER 142 
#define  OPT_OUT 141 
#define  OPT_OUTFORM 140 
#define  OPT_PASSIN 139 
#define  OPT_PASSOUT 138 
#define  OPT_R_CASES 137 
#define  OPT_SCRYPT 136 
#define  OPT_SCRYPT_N 135 
#define  OPT_SCRYPT_P 134 
#define  OPT_SCRYPT_R 133 
#define  OPT_TOPK8 132 
#define  OPT_TRADITIONAL 131 
#define  OPT_V1 130 
#define  OPT_V2 129 
#define  OPT_V2PRF 128 
 int /*<<< orphan*/ * PEM_read_bio_PKCS8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_PKCS8_PRIV_KEY_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_PKCS8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_PKCS8_PRIV_KEY_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_write_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PEM_write_bio_PrivateKey_traditional (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int PKCS12_DEFAULT_ITER ; 
 int /*<<< orphan*/ * PKCS5_pbe2_set_iv (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PKCS5_pbe2_set_scrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,long,long,long) ; 
 int /*<<< orphan*/ * PKCS5_pbe_set (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS8_decrypt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PKCS8_set0_pbe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ALGOR_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  app_passwd (char*,char*,char**,char**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int) ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int,int) ; 
 int /*<<< orphan*/ * d2i_PKCS8_PRIV_KEY_INFO_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PKCS8_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_PKCS8_PRIV_KEY_INFO_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_PKCS8_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2d_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_key (char*,int,int,char*,int /*<<< orphan*/ *,char*) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_cipher (char*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  opt_format (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_int (char*,int*) ; 
 int /*<<< orphan*/  opt_long (char*,long*) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_rand (int) ; 
 int /*<<< orphan*/  pkcs8_options ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int pkcs8_main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL;
    ENGINE *e = NULL;
    EVP_PKEY *pkey = NULL;
    PKCS8_PRIV_KEY_INFO *p8inf = NULL;
    X509_SIG *p8 = NULL;
    const EVP_CIPHER *cipher = NULL;
    char *infile = NULL, *outfile = NULL;
    char *passinarg = NULL, *passoutarg = NULL, *prog;
#ifndef OPENSSL_NO_UI_CONSOLE
    char pass[APP_PASS_LEN];
#endif
    char *passin = NULL, *passout = NULL, *p8pass = NULL;
    OPTION_CHOICE o;
    int nocrypt = 0, ret = 1, iter = PKCS12_DEFAULT_ITER;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM, topk8 = 0, pbe_nid = -1;
    int private = 0, traditional = 0;
#ifndef OPENSSL_NO_SCRYPT
    long scrypt_N = 0, scrypt_r = 0, scrypt_p = 0;
#endif

    prog = opt_init(argc, argv, pkcs8_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(pkcs8_options);
            ret = 0;
            goto end;
        case OPT_INFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &informat))
                goto opthelp;
            break;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUTFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &outformat))
                goto opthelp;
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_TOPK8:
            topk8 = 1;
            break;
        case OPT_NOITER:
            iter = 1;
            break;
        case OPT_NOCRYPT:
            nocrypt = 1;
            break;
        case OPT_R_CASES:
            if (!opt_rand(o))
                goto end;
            break;
        case OPT_TRADITIONAL:
            traditional = 1;
            break;
        case OPT_V2:
            if (!opt_cipher(opt_arg(), &cipher))
                goto opthelp;
            break;
        case OPT_V1:
            pbe_nid = OBJ_txt2nid(opt_arg());
            if (pbe_nid == NID_undef) {
                BIO_printf(bio_err,
                           "%s: Unknown PBE algorithm %s\n", prog, opt_arg());
                goto opthelp;
            }
            break;
        case OPT_V2PRF:
            pbe_nid = OBJ_txt2nid(opt_arg());
            if (!EVP_PBE_find(EVP_PBE_TYPE_PRF, pbe_nid, NULL, NULL, 0)) {
                BIO_printf(bio_err,
                           "%s: Unknown PRF algorithm %s\n", prog, opt_arg());
                goto opthelp;
            }
            if (cipher == NULL)
                cipher = EVP_aes_256_cbc();
            break;
        case OPT_ITER:
            if (!opt_int(opt_arg(), &iter))
                goto opthelp;
            break;
        case OPT_PASSIN:
            passinarg = opt_arg();
            break;
        case OPT_PASSOUT:
            passoutarg = opt_arg();
            break;
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
#ifndef OPENSSL_NO_SCRYPT
        case OPT_SCRYPT:
            scrypt_N = 16384;
            scrypt_r = 8;
            scrypt_p = 1;
            if (cipher == NULL)
                cipher = EVP_aes_256_cbc();
            break;
        case OPT_SCRYPT_N:
            if (!opt_long(opt_arg(), &scrypt_N) || scrypt_N <= 0)
                goto opthelp;
            break;
        case OPT_SCRYPT_R:
            if (!opt_long(opt_arg(), &scrypt_r) || scrypt_r <= 0)
                goto opthelp;
            break;
        case OPT_SCRYPT_P:
            if (!opt_long(opt_arg(), &scrypt_p) || scrypt_p <= 0)
                goto opthelp;
            break;
#endif
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    private = 1;

    if (!app_passwd(passinarg, passoutarg, &passin, &passout)) {
        BIO_printf(bio_err, "Error getting passwords\n");
        goto end;
    }

    if ((pbe_nid == -1) && cipher == NULL)
        cipher = EVP_aes_256_cbc();

    in = bio_open_default(infile, 'r', informat);
    if (in == NULL)
        goto end;
    out = bio_open_owner(outfile, outformat, private);
    if (out == NULL)
        goto end;

    if (topk8) {
        pkey = load_key(infile, informat, 1, passin, e, "key");
        if (pkey == NULL)
            goto end;
        if ((p8inf = EVP_PKEY2PKCS8(pkey)) == NULL) {
            BIO_printf(bio_err, "Error converting key\n");
            ERR_print_errors(bio_err);
            goto end;
        }
        if (nocrypt) {
            assert(private);
            if (outformat == FORMAT_PEM) {
                PEM_write_bio_PKCS8_PRIV_KEY_INFO(out, p8inf);
            } else if (outformat == FORMAT_ASN1) {
                i2d_PKCS8_PRIV_KEY_INFO_bio(out, p8inf);
            } else {
                BIO_printf(bio_err, "Bad format specified for key\n");
                goto end;
            }
        } else {
            X509_ALGOR *pbe;
            if (cipher) {
#ifndef OPENSSL_NO_SCRYPT
                if (scrypt_N && scrypt_r && scrypt_p)
                    pbe = PKCS5_pbe2_set_scrypt(cipher, NULL, 0, NULL,
                                                scrypt_N, scrypt_r, scrypt_p);
                else
#endif
                    pbe = PKCS5_pbe2_set_iv(cipher, iter, NULL, 0, NULL,
                                            pbe_nid);
            } else {
                pbe = PKCS5_pbe_set(pbe_nid, iter, NULL, 0);
            }
            if (pbe == NULL) {
                BIO_printf(bio_err, "Error setting PBE algorithm\n");
                ERR_print_errors(bio_err);
                goto end;
            }
            if (passout != NULL) {
                p8pass = passout;
            } else if (1) {
                /* To avoid bit rot */
#ifndef OPENSSL_NO_UI_CONSOLE
                p8pass = pass;
                if (EVP_read_pw_string
                    (pass, sizeof(pass), "Enter Encryption Password:", 1)) {
                    X509_ALGOR_free(pbe);
                    goto end;
                }
            } else {
#endif
                BIO_printf(bio_err, "Password required\n");
                goto end;
            }
            p8 = PKCS8_set0_pbe(p8pass, strlen(p8pass), p8inf, pbe);
            if (p8 == NULL) {
                X509_ALGOR_free(pbe);
                BIO_printf(bio_err, "Error encrypting key\n");
                ERR_print_errors(bio_err);
                goto end;
            }
            assert(private);
            if (outformat == FORMAT_PEM)
                PEM_write_bio_PKCS8(out, p8);
            else if (outformat == FORMAT_ASN1)
                i2d_PKCS8_bio(out, p8);
            else {
                BIO_printf(bio_err, "Bad format specified for key\n");
                goto end;
            }
        }

        ret = 0;
        goto end;
    }

    if (nocrypt) {
        if (informat == FORMAT_PEM) {
            p8inf = PEM_read_bio_PKCS8_PRIV_KEY_INFO(in, NULL, NULL, NULL);
        } else if (informat == FORMAT_ASN1) {
            p8inf = d2i_PKCS8_PRIV_KEY_INFO_bio(in, NULL);
        } else {
            BIO_printf(bio_err, "Bad format specified for key\n");
            goto end;
        }
    } else {
        if (informat == FORMAT_PEM) {
            p8 = PEM_read_bio_PKCS8(in, NULL, NULL, NULL);
        } else if (informat == FORMAT_ASN1) {
            p8 = d2i_PKCS8_bio(in, NULL);
        } else {
            BIO_printf(bio_err, "Bad format specified for key\n");
            goto end;
        }

        if (p8 == NULL) {
            BIO_printf(bio_err, "Error reading key\n");
            ERR_print_errors(bio_err);
            goto end;
        }
        if (passin != NULL) {
            p8pass = passin;
        } else if (1) {
#ifndef OPENSSL_NO_UI_CONSOLE
            p8pass = pass;
            if (EVP_read_pw_string(pass, sizeof(pass), "Enter Password:", 0)) {
                BIO_printf(bio_err, "Can't read Password\n");
                goto end;
            }
        } else {
#endif
            BIO_printf(bio_err, "Password required\n");
            goto end;
        }
        p8inf = PKCS8_decrypt(p8, p8pass, strlen(p8pass));
    }

    if (p8inf == NULL) {
        BIO_printf(bio_err, "Error decrypting key\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    if ((pkey = EVP_PKCS82PKEY(p8inf)) == NULL) {
        BIO_printf(bio_err, "Error converting key\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    assert(private);
    if (outformat == FORMAT_PEM) {
        if (traditional)
            PEM_write_bio_PrivateKey_traditional(out, pkey, NULL, NULL, 0,
                                                 NULL, passout);
        else
            PEM_write_bio_PrivateKey(out, pkey, NULL, NULL, 0, NULL, passout);
    } else if (outformat == FORMAT_ASN1) {
        i2d_PrivateKey_bio(out, pkey);
    } else {
        BIO_printf(bio_err, "Bad format specified for key\n");
        goto end;
    }
    ret = 0;

 end:
    X509_SIG_free(p8);
    PKCS8_PRIV_KEY_INFO_free(p8inf);
    EVP_PKEY_free(pkey);
    release_engine(e);
    BIO_free_all(out);
    BIO_free(in);
    OPENSSL_free(passin);
    OPENSSL_free(passout);

    return ret;
}