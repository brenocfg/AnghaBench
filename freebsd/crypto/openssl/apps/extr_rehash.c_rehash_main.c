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
typedef  enum Hash { ____Placeholder_Hash } Hash ;
typedef  int OPTION_CHOICE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  EVP_MD_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int HASH_BOTH ; 
 int HASH_NEW ; 
 int HASH_OLD ; 
 char LIST_SEPARATOR_CHAR ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
#define  OPT_COMPAT 134 
#define  OPT_EOF 133 
#define  OPT_ERR 132 
#define  OPT_HELP 131 
#define  OPT_N 130 
#define  OPT_OLD 129 
#define  OPT_VERBOSE 128 
 char* X509_get_default_cert_dir () ; 
 int /*<<< orphan*/  X509_get_default_cert_dir_env () ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ do_dir (char*,int) ; 
 int /*<<< orphan*/  evpmd ; 
 int /*<<< orphan*/  evpmdsize ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 int opt_num_rest () ; 
 char** opt_rest () ; 
 int /*<<< orphan*/  rehash_options ; 
 int /*<<< orphan*/  remove_links ; 
 char* strtok (char*,char*) ; 
 int verbose ; 

int rehash_main(int argc, char **argv)
{
    const char *env, *prog;
    char *e, *m;
    int errs = 0;
    OPTION_CHOICE o;
    enum Hash h = HASH_NEW;

    prog = opt_init(argc, argv, rehash_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(rehash_options);
            goto end;
        case OPT_COMPAT:
            h = HASH_BOTH;
            break;
        case OPT_OLD:
            h = HASH_OLD;
            break;
        case OPT_N:
            remove_links = 0;
            break;
        case OPT_VERBOSE:
            verbose = 1;
            break;
        }
    }
    argc = opt_num_rest();
    argv = opt_rest();

    evpmd = EVP_sha1();
    evpmdsize = EVP_MD_size(evpmd);

    if (*argv != NULL) {
        while (*argv != NULL)
            errs += do_dir(*argv++, h);
    } else if ((env = getenv(X509_get_default_cert_dir_env())) != NULL) {
        char lsc[2] = { LIST_SEPARATOR_CHAR, '\0' };
        m = OPENSSL_strdup(env);
        for (e = strtok(m, lsc); e != NULL; e = strtok(NULL, lsc))
            errs += do_dir(e, h);
        OPENSSL_free(m);
    } else {
        errs += do_dir(X509_get_default_cert_dir(), h);
    }

 end:
    return errs;
}