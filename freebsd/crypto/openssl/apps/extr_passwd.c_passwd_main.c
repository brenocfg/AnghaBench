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
typedef  int /*<<< orphan*/  trash ;
typedef  scalar_t__ passwd_modes ;
typedef  int OPTION_CHOICE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int BIO_gets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int BUFSIZ ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_read_pw_string (char*,size_t,char*,int) ; 
 int /*<<< orphan*/  FORMAT_TEXT ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
#define  OPT_1 144 
#define  OPT_5 143 
#define  OPT_6 142 
#define  OPT_AIXMD5 141 
#define  OPT_APR1 140 
#define  OPT_CRYPT 139 
#define  OPT_EOF 138 
#define  OPT_ERR 137 
#define  OPT_HELP 136 
#define  OPT_IN 135 
#define  OPT_NOVERIFY 134 
#define  OPT_QUIET 133 
#define  OPT_REVERSE 132 
#define  OPT_R_CASES 131 
#define  OPT_SALT 130 
#define  OPT_STDIN 129 
#define  OPT_TABLE 128 
 char* app_malloc (size_t,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/ * bio_open_default (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  do_passwd (int,char**,char**,char*,int /*<<< orphan*/ ,int,int,int,size_t,scalar_t__) ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 int /*<<< orphan*/  opt_rand (int) ; 
 char** opt_rest () ; 
 scalar_t__ passwd_aixmd5 ; 
 scalar_t__ passwd_apr1 ; 
 scalar_t__ passwd_crypt ; 
 scalar_t__ passwd_md5 ; 
 int /*<<< orphan*/  passwd_options ; 
 scalar_t__ passwd_sha256 ; 
 scalar_t__ passwd_sha512 ; 
 scalar_t__ passwd_unset ; 
 char* strchr (char*,char) ; 

int passwd_main(int argc, char **argv)
{
    BIO *in = NULL;
    char *infile = NULL, *salt = NULL, *passwd = NULL, **passwds = NULL;
    char *salt_malloc = NULL, *passwd_malloc = NULL, *prog;
    OPTION_CHOICE o;
    int in_stdin = 0, pw_source_defined = 0;
#ifndef OPENSSL_NO_UI_CONSOLE
    int in_noverify = 0;
#endif
    int passed_salt = 0, quiet = 0, table = 0, reverse = 0;
    int ret = 1;
    passwd_modes mode = passwd_unset;
    size_t passwd_malloc_size = 0;
    size_t pw_maxlen = 256; /* arbitrary limit, should be enough for most
                             * passwords */

    prog = opt_init(argc, argv, passwd_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
 opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(passwd_options);
            ret = 0;
            goto end;
        case OPT_IN:
            if (pw_source_defined)
                goto opthelp;
            infile = opt_arg();
            pw_source_defined = 1;
            break;
        case OPT_NOVERIFY:
#ifndef OPENSSL_NO_UI_CONSOLE
            in_noverify = 1;
#endif
            break;
        case OPT_QUIET:
            quiet = 1;
            break;
        case OPT_TABLE:
            table = 1;
            break;
        case OPT_REVERSE:
            reverse = 1;
            break;
        case OPT_1:
            if (mode != passwd_unset)
                goto opthelp;
            mode = passwd_md5;
            break;
        case OPT_5:
            if (mode != passwd_unset)
                goto opthelp;
            mode = passwd_sha256;
            break;
        case OPT_6:
            if (mode != passwd_unset)
                goto opthelp;
            mode = passwd_sha512;
            break;
        case OPT_APR1:
            if (mode != passwd_unset)
                goto opthelp;
            mode = passwd_apr1;
            break;
        case OPT_AIXMD5:
            if (mode != passwd_unset)
                goto opthelp;
            mode = passwd_aixmd5;
            break;
        case OPT_CRYPT:
#ifndef OPENSSL_NO_DES
            if (mode != passwd_unset)
                goto opthelp;
            mode = passwd_crypt;
#endif
            break;
        case OPT_SALT:
            passed_salt = 1;
            salt = opt_arg();
            break;
        case OPT_STDIN:
            if (pw_source_defined)
                goto opthelp;
            in_stdin = 1;
            pw_source_defined = 1;
            break;
        case OPT_R_CASES:
            if (!opt_rand(o))
                goto end;
            break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();

    if (*argv != NULL) {
        if (pw_source_defined)
            goto opthelp;
        pw_source_defined = 1;
        passwds = argv;
    }

    if (mode == passwd_unset) {
        /* use default */
        mode = passwd_crypt;
    }

#ifdef OPENSSL_NO_DES
    if (mode == passwd_crypt)
        goto opthelp;
#endif

    if (infile != NULL && in_stdin) {
        BIO_printf(bio_err, "%s: Can't combine -in and -stdin\n", prog);
        goto end;
    }

    if (infile != NULL || in_stdin) {
        /*
         * If in_stdin is true, we know that infile is NULL, and that
         * bio_open_default() will give us back an alias for stdin.
         */
        in = bio_open_default(infile, 'r', FORMAT_TEXT);
        if (in == NULL)
            goto end;
    }

    if (mode == passwd_crypt)
        pw_maxlen = 8;

    if (passwds == NULL) {
        /* no passwords on the command line */

        passwd_malloc_size = pw_maxlen + 2;
        /* longer than necessary so that we can warn about truncation */
        passwd = passwd_malloc =
            app_malloc(passwd_malloc_size, "password buffer");
    }

    if ((in == NULL) && (passwds == NULL)) {
        /*
         * we use the following method to make sure what
         * in the 'else' section is always compiled, to
         * avoid rot of not-frequently-used code.
         */
        if (1) {
#ifndef OPENSSL_NO_UI_CONSOLE
            /* build a null-terminated list */
            static char *passwds_static[2] = { NULL, NULL };

            passwds = passwds_static;
            if (in == NULL) {
                if (EVP_read_pw_string
                    (passwd_malloc, passwd_malloc_size, "Password: ",
                     !(passed_salt || in_noverify)) != 0)
                    goto end;
            }
            passwds[0] = passwd_malloc;
        } else {
#endif
            BIO_printf(bio_err, "password required\n");
            goto end;
        }
    }

    if (in == NULL) {
        assert(passwds != NULL);
        assert(*passwds != NULL);

        do {                    /* loop over list of passwords */
            passwd = *passwds++;
            if (!do_passwd(passed_salt, &salt, &salt_malloc, passwd, bio_out,
                           quiet, table, reverse, pw_maxlen, mode))
                goto end;
        } while (*passwds != NULL);
    } else {
        /* in != NULL */
        int done;

        assert(passwd != NULL);
        do {
            int r = BIO_gets(in, passwd, pw_maxlen + 1);
            if (r > 0) {
                char *c = (strchr(passwd, '\n'));
                if (c != NULL) {
                    *c = 0;     /* truncate at newline */
                } else {
                    /* ignore rest of line */
                    char trash[BUFSIZ];
                    do
                        r = BIO_gets(in, trash, sizeof(trash));
                    while ((r > 0) && (!strchr(trash, '\n')));
                }

                if (!do_passwd
                    (passed_salt, &salt, &salt_malloc, passwd, bio_out, quiet,
                     table, reverse, pw_maxlen, mode))
                    goto end;
            }
            done = (r <= 0);
        } while (!done);
    }
    ret = 0;

 end:
#if 0
    ERR_print_errors(bio_err);
#endif
    OPENSSL_free(salt_malloc);
    OPENSSL_free(passwd_malloc);
    BIO_free(in);
    return ret;
}