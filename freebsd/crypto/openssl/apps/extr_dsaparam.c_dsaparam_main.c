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
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BN_GENCB_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_GENCB_new () ; 
 int /*<<< orphan*/  BN_GENCB_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_generate_parameters_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int /*<<< orphan*/ * DSAparams_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSAparams_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_PEM ; 
 int OPENSSL_DSA_MAX_MODULUS_BITS ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
#define  OPT_C 140 
#define  OPT_ENGINE 139 
#define  OPT_EOF 138 
#define  OPT_ERR 137 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
#define  OPT_GENKEY 136 
#define  OPT_HELP 135 
#define  OPT_IN 134 
#define  OPT_INFORM 133 
#define  OPT_NOOUT 132 
#define  OPT_OUT 131 
#define  OPT_OUTFORM 130 
#define  OPT_R_CASES 129 
#define  OPT_TEXT 128 
 int /*<<< orphan*/ * PEM_read_bio_DSAparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PEM_write_bio_DSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PEM_write_bio_DSAparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* app_malloc (int,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int) ; 
 int /*<<< orphan*/ * bio_open_owner (char*,int,int) ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/ * d2i_DSAparams_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_cb ; 
 int /*<<< orphan*/  dsaparam_options ; 
 int i2d_DSAPrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i2d_DSAparams_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_format (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_int (char*,int*) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_rand (int) ; 
 char** opt_rest () ; 
 int /*<<< orphan*/  print_bignum_var (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,int,unsigned char*) ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int dsaparam_main(int argc, char **argv)
{
    ENGINE *e = NULL;
    DSA *dsa = NULL;
    BIO *in = NULL, *out = NULL;
    BN_GENCB *cb = NULL;
    int numbits = -1, num = 0, genkey = 0;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM, noout = 0, C = 0;
    int ret = 1, i, text = 0, private = 0;
    char *infile = NULL, *outfile = NULL, *prog;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, dsaparam_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(dsaparam_options);
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
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        case OPT_TEXT:
            text = 1;
            break;
        case OPT_C:
            C = 1;
            break;
        case OPT_GENKEY:
            genkey = 1;
            break;
        case OPT_R_CASES:
            if (!opt_rand(o))
                goto end;
            break;
        case OPT_NOOUT:
            noout = 1;
            break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();

    if (argc == 1) {
        if (!opt_int(argv[0], &num) || num < 0)
            goto end;
        /* generate a key */
        numbits = num;
    }
    private = genkey ? 1 : 0;

    in = bio_open_default(infile, 'r', informat);
    if (in == NULL)
        goto end;
    out = bio_open_owner(outfile, outformat, private);
    if (out == NULL)
        goto end;

    if (numbits > 0) {
        if (numbits > OPENSSL_DSA_MAX_MODULUS_BITS)
            BIO_printf(bio_err,
                       "Warning: It is not recommended to use more than %d bit for DSA keys.\n"
                       "         Your key size is %d! Larger key size may behave not as expected.\n",
                       OPENSSL_DSA_MAX_MODULUS_BITS, numbits);

        cb = BN_GENCB_new();
        if (cb == NULL) {
            BIO_printf(bio_err, "Error allocating BN_GENCB object\n");
            goto end;
        }
        BN_GENCB_set(cb, dsa_cb, bio_err);
        dsa = DSA_new();
        if (dsa == NULL) {
            BIO_printf(bio_err, "Error allocating DSA object\n");
            goto end;
        }
        BIO_printf(bio_err, "Generating DSA parameters, %d bit long prime\n",
                   num);
        BIO_printf(bio_err, "This could take some time\n");
        if (!DSA_generate_parameters_ex(dsa, num, NULL, 0, NULL, NULL, cb)) {
            ERR_print_errors(bio_err);
            BIO_printf(bio_err, "Error, DSA key generation failed\n");
            goto end;
        }
    } else if (informat == FORMAT_ASN1) {
        dsa = d2i_DSAparams_bio(in, NULL);
    } else {
        dsa = PEM_read_bio_DSAparams(in, NULL, NULL, NULL);
    }
    if (dsa == NULL) {
        BIO_printf(bio_err, "unable to load DSA parameters\n");
        ERR_print_errors(bio_err);
        goto end;
    }

    if (text) {
        DSAparams_print(out, dsa);
    }

    if (C) {
        const BIGNUM *p = NULL, *q = NULL, *g = NULL;
        unsigned char *data;
        int len, bits_p;

        DSA_get0_pqg(dsa, &p, &q, &g);
        len = BN_num_bytes(p);
        bits_p = BN_num_bits(p);

        data = app_malloc(len + 20, "BN space");

        BIO_printf(bio_out, "static DSA *get_dsa%d(void)\n{\n", bits_p);
        print_bignum_var(bio_out, p, "dsap", bits_p, data);
        print_bignum_var(bio_out, q, "dsaq", bits_p, data);
        print_bignum_var(bio_out, g, "dsag", bits_p, data);
        BIO_printf(bio_out, "    DSA *dsa = DSA_new();\n"
                            "    BIGNUM *p, *q, *g;\n"
                            "\n");
        BIO_printf(bio_out, "    if (dsa == NULL)\n"
                            "        return NULL;\n");
        BIO_printf(bio_out, "    if (!DSA_set0_pqg(dsa, p = BN_bin2bn(dsap_%d, sizeof(dsap_%d), NULL),\n",
                   bits_p, bits_p);
        BIO_printf(bio_out, "                           q = BN_bin2bn(dsaq_%d, sizeof(dsaq_%d), NULL),\n",
                   bits_p, bits_p);
        BIO_printf(bio_out, "                           g = BN_bin2bn(dsag_%d, sizeof(dsag_%d), NULL))) {\n",
                   bits_p, bits_p);
        BIO_printf(bio_out, "        DSA_free(dsa);\n"
                            "        BN_free(p);\n"
                            "        BN_free(q);\n"
                            "        BN_free(g);\n"
                            "        return NULL;\n"
                            "    }\n"
                            "    return dsa;\n}\n");
        OPENSSL_free(data);
    }

    if (outformat == FORMAT_ASN1 && genkey)
        noout = 1;

    if (!noout) {
        if (outformat == FORMAT_ASN1)
            i = i2d_DSAparams_bio(out, dsa);
        else
            i = PEM_write_bio_DSAparams(out, dsa);
        if (!i) {
            BIO_printf(bio_err, "unable to write DSA parameters\n");
            ERR_print_errors(bio_err);
            goto end;
        }
    }
    if (genkey) {
        DSA *dsakey;

        if ((dsakey = DSAparams_dup(dsa)) == NULL)
            goto end;
        if (!DSA_generate_key(dsakey)) {
            ERR_print_errors(bio_err);
            DSA_free(dsakey);
            goto end;
        }
        assert(private);
        if (outformat == FORMAT_ASN1)
            i = i2d_DSAPrivateKey_bio(out, dsakey);
        else
            i = PEM_write_bio_DSAPrivateKey(out, dsakey, NULL, NULL, 0, NULL,
                                            NULL);
        DSA_free(dsakey);
    }
    ret = 0;
 end:
    BN_GENCB_free(cb);
    BIO_free(in);
    BIO_free_all(out);
    DSA_free(dsa);
    release_engine(e);
    return ret;
}