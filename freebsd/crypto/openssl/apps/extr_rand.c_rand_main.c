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
typedef  int /*<<< orphan*/  buf ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_f_base64 () ; 
 scalar_t__ BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int BIO_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int FORMAT_BASE64 ; 
 int FORMAT_BINARY ; 
 int FORMAT_TEXT ; 
#define  OPT_BASE64 135 
#define  OPT_ENGINE 134 
#define  OPT_EOF 133 
#define  OPT_ERR 132 
#define  OPT_HELP 131 
#define  OPT_HEX 130 
#define  OPT_OUT 129 
#define  OPT_R_CASES 128 
 int RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_int (char*,int*) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_rand (int) ; 
 char** opt_rest () ; 
 int /*<<< orphan*/  rand_options ; 
 int /*<<< orphan*/  release_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_engine (char*,int /*<<< orphan*/ ) ; 

int rand_main(int argc, char **argv)
{
    ENGINE *e = NULL;
    BIO *out = NULL;
    char *outfile = NULL, *prog;
    OPTION_CHOICE o;
    int format = FORMAT_BINARY, i, num = -1, r, ret = 1;

    prog = opt_init(argc, argv, rand_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(rand_options);
            ret = 0;
            goto end;
        case OPT_OUT:
            outfile = opt_arg();
            break;
        case OPT_ENGINE:
            e = setup_engine(opt_arg(), 0);
            break;
        case OPT_R_CASES:
            if (!opt_rand(o))
                goto end;
            break;
        case OPT_BASE64:
            format = FORMAT_BASE64;
            break;
        case OPT_HEX:
            format = FORMAT_TEXT;
            break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();
    if (argc == 1) {
        if (!opt_int(argv[0], &num) || num <= 0)
            goto end;
    } else if (argc > 0) {
        BIO_printf(bio_err, "Extra arguments given.\n");
        goto opthelp;
    }

    out = bio_open_default(outfile, 'w', format);
    if (out == NULL)
        goto end;

    if (format == FORMAT_BASE64) {
        BIO *b64 = BIO_new(BIO_f_base64());
        if (b64 == NULL)
            goto end;
        out = BIO_push(b64, out);
    }

    while (num > 0) {
        unsigned char buf[4096];
        int chunk;

        chunk = num;
        if (chunk > (int)sizeof(buf))
            chunk = sizeof(buf);
        r = RAND_bytes(buf, chunk);
        if (r <= 0)
            goto end;
        if (format != FORMAT_TEXT) {
            if (BIO_write(out, buf, chunk) != chunk)
                goto end;
        } else {
            for (i = 0; i < chunk; i++)
                if (BIO_printf(out, "%02x", buf[i]) != 2)
                    goto end;
        }
        num -= chunk;
    }
    if (format == FORMAT_TEXT)
        BIO_puts(out, "\n");
    if (BIO_flush(out) <= 0)
        goto end;

    ret = 0;

 end:
    if (ret != 0)
        ERR_print_errors(bio_err);
    release_engine(e);
    BIO_free_all(out);
    return ret;
}