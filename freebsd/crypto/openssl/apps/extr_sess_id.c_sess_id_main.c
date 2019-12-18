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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int FORMAT_ASN1 ; 
 int FORMAT_NSS ; 
 int FORMAT_PEM ; 
#define  OPT_CERT 138 
#define  OPT_CONTEXT 137 
#define  OPT_EOF 136 
#define  OPT_ERR 135 
 int OPT_FMT_NSS ; 
 int OPT_FMT_PEMDER ; 
#define  OPT_HELP 134 
#define  OPT_IN 133 
#define  OPT_INFORM 132 
#define  OPT_NOOUT 131 
#define  OPT_OUT 130 
#define  OPT_OUTFORM 129 
#define  OPT_TEXT 128 
 int PEM_write_bio_SSL_SESSION (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PEM_write_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t SSL_MAX_SID_CTX_LENGTH ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_SESSION_get0_peer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSL_SESSION_print_keylog (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_set1_id_context (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  X509_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int) ; 
 int i2d_SSL_SESSION_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ i2d_X509_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_sess_id (char*,int) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_format (char*,int,int*) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  sess_id_options ; 
 size_t strlen (char*) ; 

int sess_id_main(int argc, char **argv)
{
    SSL_SESSION *x = NULL;
    X509 *peer = NULL;
    BIO *out = NULL;
    char *infile = NULL, *outfile = NULL, *context = NULL, *prog;
    int informat = FORMAT_PEM, outformat = FORMAT_PEM;
    int cert = 0, noout = 0, text = 0, ret = 1, i, num = 0;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, sess_id_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(sess_id_options);
            ret = 0;
            goto end;
        case OPT_INFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &informat))
                goto opthelp;
            break;
        case OPT_OUTFORM:
            if (!opt_format(opt_arg(), OPT_FMT_PEMDER | OPT_FMT_NSS,
                            &outformat))
                goto opthelp;
            break;
        case OPT_IN:
            infile = opt_arg();
            break;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_TEXT:
            text = ++num;
            break;
        case OPT_CERT:
            cert = ++num;
            break;
        case OPT_NOOUT:
            noout = ++num;
            break;
        case OPT_CONTEXT:
            context = opt_arg();
            break;
        }
    }
    argc = opt_num_rest();
    if (argc != 0)
        goto opthelp;

    x = load_sess_id(infile, informat);
    if (x == NULL) {
        goto end;
    }
    peer = SSL_SESSION_get0_peer(x);

    if (context != NULL) {
        size_t ctx_len = strlen(context);
        if (ctx_len > SSL_MAX_SID_CTX_LENGTH) {
            BIO_printf(bio_err, "Context too long\n");
            goto end;
        }
        if (!SSL_SESSION_set1_id_context(x, (unsigned char *)context,
                                         ctx_len)) {
            BIO_printf(bio_err, "Error setting id context\n");
            goto end;
        }
    }

    if (!noout || text) {
        out = bio_open_default(outfile, 'w', outformat);
        if (out == NULL)
            goto end;
    }

    if (text) {
        SSL_SESSION_print(out, x);

        if (cert) {
            if (peer == NULL)
                BIO_puts(out, "No certificate present\n");
            else
                X509_print(out, peer);
        }
    }

    if (!noout && !cert) {
        if (outformat == FORMAT_ASN1) {
            i = i2d_SSL_SESSION_bio(out, x);
        } else if (outformat == FORMAT_PEM) {
            i = PEM_write_bio_SSL_SESSION(out, x);
        } else if (outformat == FORMAT_NSS) {
            i = SSL_SESSION_print_keylog(out, x);
        } else {
            BIO_printf(bio_err, "bad output format specified for outfile\n");
            goto end;
        }
        if (!i) {
            BIO_printf(bio_err, "unable to write SSL_SESSION\n");
            goto end;
        }
    } else if (!noout && (peer != NULL)) { /* just print the certificate */
        if (outformat == FORMAT_ASN1) {
            i = (int)i2d_X509_bio(out, peer);
        } else if (outformat == FORMAT_PEM) {
            i = PEM_write_bio_X509(out, peer);
        } else {
            BIO_printf(bio_err, "bad output format specified for outfile\n");
            goto end;
        }
        if (!i) {
            BIO_printf(bio_err, "unable to write X509\n");
            goto end;
        }
    }
    ret = 0;
 end:
    BIO_free_all(out);
    SSL_SESSION_free(x);
    return ret;
}