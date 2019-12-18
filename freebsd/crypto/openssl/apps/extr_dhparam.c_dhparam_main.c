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
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ BIO_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_GENCB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_GENCB_new () ; 
 int /*<<< orphan*/  BN_GENCB_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DEFBITS ; 
 int DH_CHECK_INVALID_J_VALUE ; 
 int DH_CHECK_INVALID_Q_VALUE ; 
 int DH_CHECK_P_NOT_PRIME ; 
 int DH_CHECK_P_NOT_SAFE_PRIME ; 
 int DH_CHECK_Q_NOT_PRIME ; 
 int DH_NOT_SUITABLE_GENERATOR ; 
 int DH_UNABLE_TO_CHECK_GENERATOR ; 
 int DH_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_check (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_generate_parameters_ex (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DH_get_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_new () ; 
 int DH_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DHparams_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_dup_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_generate_parameters_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ *) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_PEM ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
#define  OPT_2 143 
#define  OPT_5 142 
#define  OPT_C 141 
#define  OPT_CHECK 140 
#define  OPT_DSAPARAM 139 
#define  OPT_ENGINE 138 
#define  OPT_EOF 137 
#define  OPT_ERR 136 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
#define  OPT_HELP 135 
#define  OPT_IN 134 
#define  OPT_INFORM 133 
#define  OPT_NOOUT 132 
#define  OPT_OUT 131 
#define  OPT_OUTFORM 130 
#define  OPT_R_CASES 129 
#define  OPT_TEXT 128 
 int /*<<< orphan*/ * PEM_read_bio_DHparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_DSAparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PEM_write_bio_DHparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PEM_write_bio_DHxparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* app_malloc (int,char*) ; 
 int /*<<< orphan*/ * bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int) ; 
 int /*<<< orphan*/ * d2i_DHparams_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_DHxparams_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_DSAparams_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dh_cb ; 
 int /*<<< orphan*/  dhparam_options ; 
 int i2d_DHparams_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_DHxparams_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_format (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_int (char*,int*) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_rand (int) ; 
 char** opt_rest () ; 
 int /*<<< orphan*/  print_bignum_var (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int dhparam_main(int argc, char **argv)
{
    BIO *in = NULL, *out = NULL;
    DH *dh = NULL;
    char *infile = NULL, *outfile = NULL, *prog;
    ENGINE *e = NULL;
#ifndef OPENSSL_NO_DSA
    int dsaparam = 0;
#endif
    int i, text = 0, C = 0, ret = 1, num = 0, g = 0;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM, check = 0, noout = 0;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, dhparam_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(dhparam_options);
            ret = 0;
            goto end;
        case OPT_INFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &informat))
                goto opthelp;
            break;
        case OPT_OUTFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &outformat))
                goto opthelp;
            break;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        case OPT_CHECK:
            check = 1;
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_DSAPARAM:
#ifndef OPENSSL_NO_DSA
            dsaparam = 1;
#endif
            break;
        case OPT_C:
            C = 1;
            break;
        case OPT_2:
            g = 2;
            break;
        case OPT_5:
            g = 5;
            break;
        case OPT_NOOUT:
            noout = 1;
            break;
        case OPT_R_CASES:
            if (!opt_rand(o))
                goto end;
            break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();

    if (argv[0] != NULL && (!opt_int(argv[0], &num) || num <= 0))
        goto end;

    if (g && !num)
        num = DEFBITS;

# ifndef OPENSSL_NO_DSA
    if (dsaparam && g) {
        BIO_printf(bio_err,
                   "generator may not be chosen for DSA parameters\n");
        goto end;
    }
# endif

    out = bio_open_default(outfile, 'w', outformat);
    if (out == NULL)
        goto end;

    /* DH parameters */
    if (num && !g)
        g = 2;

    if (num) {

        BN_GENCB *cb;
        cb = BN_GENCB_new();
        if (cb == NULL) {
            ERR_print_errors(bio_err);
            goto end;
        }

        BN_GENCB_set(cb, dh_cb, bio_err);

# ifndef OPENSSL_NO_DSA
        if (dsaparam) {
            DSA *dsa = DSA_new();

            BIO_printf(bio_err,
                       "Generating DSA parameters, %d bit long prime\n", num);
            if (dsa == NULL
                || !DSA_generate_parameters_ex(dsa, num, NULL, 0, NULL, NULL,
                                               cb)) {
                DSA_free(dsa);
                BN_GENCB_free(cb);
                ERR_print_errors(bio_err);
                goto end;
            }

            dh = DSA_dup_DH(dsa);
            DSA_free(dsa);
            if (dh == NULL) {
                BN_GENCB_free(cb);
                ERR_print_errors(bio_err);
                goto end;
            }
        } else
# endif
        {
            dh = DH_new();
            BIO_printf(bio_err,
                       "Generating DH parameters, %d bit long safe prime, generator %d\n",
                       num, g);
            BIO_printf(bio_err, "This is going to take a long time\n");
            if (dh == NULL || !DH_generate_parameters_ex(dh, num, g, cb)) {
                BN_GENCB_free(cb);
                ERR_print_errors(bio_err);
                goto end;
            }
        }

        BN_GENCB_free(cb);
    } else {

        in = bio_open_default(infile, 'r', informat);
        if (in == NULL)
            goto end;

# ifndef OPENSSL_NO_DSA
        if (dsaparam) {
            DSA *dsa;

            if (informat == FORMAT_ASN1)
                dsa = d2i_DSAparams_bio(in, NULL);
            else                /* informat == FORMAT_PEM */
                dsa = PEM_read_bio_DSAparams(in, NULL, NULL, NULL);

            if (dsa == NULL) {
                BIO_printf(bio_err, "unable to load DSA parameters\n");
                ERR_print_errors(bio_err);
                goto end;
            }

            dh = DSA_dup_DH(dsa);
            DSA_free(dsa);
            if (dh == NULL) {
                ERR_print_errors(bio_err);
                goto end;
            }
        } else
# endif
        {
            if (informat == FORMAT_ASN1) {
                /*
                 * We have no PEM header to determine what type of DH params it
                 * is. We'll just try both.
                 */
                dh = d2i_DHparams_bio(in, NULL);
                /* BIO_reset() returns 0 for success for file BIOs only!!! */
                if (dh == NULL && BIO_reset(in) == 0)
                    dh = d2i_DHxparams_bio(in, NULL);
            } else {
                /* informat == FORMAT_PEM */
                dh = PEM_read_bio_DHparams(in, NULL, NULL, NULL);
            }

            if (dh == NULL) {
                BIO_printf(bio_err, "unable to load DH parameters\n");
                ERR_print_errors(bio_err);
                goto end;
            }
        }

        /* dh != NULL */
    }

    if (text) {
        DHparams_print(out, dh);
    }

    if (check) {
        if (!DH_check(dh, &i)) {
            ERR_print_errors(bio_err);
            goto end;
        }
        if (i & DH_CHECK_P_NOT_PRIME)
            BIO_printf(bio_err, "WARNING: p value is not prime\n");
        if (i & DH_CHECK_P_NOT_SAFE_PRIME)
            BIO_printf(bio_err, "WARNING: p value is not a safe prime\n");
        if (i & DH_CHECK_Q_NOT_PRIME)
            BIO_printf(bio_err, "WARNING: q value is not a prime\n");
        if (i & DH_CHECK_INVALID_Q_VALUE)
            BIO_printf(bio_err, "WARNING: q value is invalid\n");
        if (i & DH_CHECK_INVALID_J_VALUE)
            BIO_printf(bio_err, "WARNING: j value is invalid\n");
        if (i & DH_UNABLE_TO_CHECK_GENERATOR)
            BIO_printf(bio_err,
                       "WARNING: unable to check the generator value\n");
        if (i & DH_NOT_SUITABLE_GENERATOR)
            BIO_printf(bio_err, "WARNING: the g value is not a generator\n");
        if (i == 0)
            BIO_printf(bio_err, "DH parameters appear to be ok.\n");
        if (num != 0 && i != 0) {
            /*
             * We have generated parameters but DH_check() indicates they are
             * invalid! This should never happen!
             */
            BIO_printf(bio_err, "ERROR: Invalid parameters generated\n");
            goto end;
        }
    }
    if (C) {
        unsigned char *data;
        int len, bits;
        const BIGNUM *pbn, *gbn;

        len = DH_size(dh);
        bits = DH_bits(dh);
        DH_get0_pqg(dh, &pbn, NULL, &gbn);
        data = app_malloc(len, "print a BN");

        BIO_printf(out, "static DH *get_dh%d(void)\n{\n", bits);
        print_bignum_var(out, pbn, "dhp", bits, data);
        print_bignum_var(out, gbn, "dhg", bits, data);
        BIO_printf(out, "    DH *dh = DH_new();\n"
                        "    BIGNUM *p, *g;\n"
                        "\n"
                        "    if (dh == NULL)\n"
                        "        return NULL;\n");
        BIO_printf(out, "    p = BN_bin2bn(dhp_%d, sizeof(dhp_%d), NULL);\n",
                   bits, bits);
        BIO_printf(out, "    g = BN_bin2bn(dhg_%d, sizeof(dhg_%d), NULL);\n",
                   bits, bits);
        BIO_printf(out, "    if (p == NULL || g == NULL\n"
                        "            || !DH_set0_pqg(dh, p, NULL, g)) {\n"
                        "        DH_free(dh);\n"
                        "        BN_free(p);\n"
                        "        BN_free(g);\n"
                        "        return NULL;\n"
                        "    }\n");
        if (DH_get_length(dh) > 0)
            BIO_printf(out,
                        "    if (!DH_set_length(dh, %ld)) {\n"
                        "        DH_free(dh);\n"
                        "        return NULL;\n"
                        "    }\n", DH_get_length(dh));
        BIO_printf(out, "    return dh;\n}\n");
        OPENSSL_free(data);
    }

    if (!noout) {
        const BIGNUM *q;
        DH_get0_pqg(dh, NULL, &q, NULL);
        if (outformat == FORMAT_ASN1) {
            if (q != NULL)
                i = i2d_DHxparams_bio(out, dh);
            else
                i = i2d_DHparams_bio(out, dh);
        } else if (q != NULL) {
            i = PEM_write_bio_DHxparams(out, dh);
        } else {
            i = PEM_write_bio_DHparams(out, dh);
        }
        if (!i) {
            BIO_printf(bio_err, "unable to write DH parameters\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }
    ret = 0;
 end:
    BIO_free(in);
    BIO_free_all(out);
    DH_free(dh);
    release_engine(e);
    return ret;
}