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

/* Variables and functions */
 char* BF_options () ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 char* BN_options () ; 
 char* DES_options () ; 
#define  DEVRANDOM 141 
#define  DEVRANDOM_EGD 140 
 char* IDEA_options () ; 
 char* MD2_options () ; 
 int /*<<< orphan*/  OPENSSL_BUILT_ON ; 
 int /*<<< orphan*/  OPENSSL_CFLAGS ; 
 int /*<<< orphan*/  OPENSSL_DIR ; 
 int /*<<< orphan*/  OPENSSL_ENGINES_DIR ; 
 int /*<<< orphan*/  OPENSSL_PLATFORM ; 
 int /*<<< orphan*/  OPENSSL_VERSION ; 
 scalar_t__ OPENSSL_VERSION_NUMBER ; 
 char* OPENSSL_VERSION_TEXT ; 
#define  OPT_A 139 
#define  OPT_B 138 
#define  OPT_D 137 
#define  OPT_E 136 
#define  OPT_EOF 135 
#define  OPT_ERR 134 
#define  OPT_F 133 
#define  OPT_HELP 132 
#define  OPT_O 131 
#define  OPT_P 130 
#define  OPT_R 129 
#define  OPT_V 128 
 char* OpenSSL_version (int /*<<< orphan*/ ) ; 
 scalar_t__ OpenSSL_version_num () ; 
 char* RC4_options () ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 scalar_t__ opt_num_rest () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printlist (char*,char const**) ; 
 int /*<<< orphan*/  version_options ; 

int version_main(int argc, char **argv)
{
    int ret = 1, dirty = 0, seed = 0;
    int cflags = 0, version = 0, date = 0, options = 0, platform = 0, dir = 0;
    int engdir = 0;
    char *prog;
    OPTION_CHOICE o;

    prog = opt_init(argc, argv, version_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:
        case OPT_ERR:
opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            goto end;
        case OPT_HELP:
            opt_help(version_options);
            ret = 0;
            goto end;
        case OPT_B:
            dirty = date = 1;
            break;
        case OPT_D:
            dirty = dir = 1;
            break;
        case OPT_E:
            dirty = engdir = 1;
            break;
        case OPT_F:
            dirty = cflags = 1;
            break;
        case OPT_O:
            dirty = options = 1;
            break;
        case OPT_P:
            dirty = platform = 1;
            break;
        case OPT_R:
            dirty = seed = 1;
            break;
        case OPT_V:
            dirty = version = 1;
            break;
        case OPT_A:
            seed = options = cflags = version = date = platform = dir = engdir
                = 1;
            break;
        }
    }
    if (opt_num_rest() != 0) {
        BIO_printf(bio_err, "Extra parameters given.\n");
        goto opthelp;
    }
    if (!dirty)
        version = 1;

    if (version) {
        if (OpenSSL_version_num() == OPENSSL_VERSION_NUMBER)
            printf("%s\n", OpenSSL_version(OPENSSL_VERSION));
        else
            printf("%s (Library: %s)\n",
                   OPENSSL_VERSION_TEXT, OpenSSL_version(OPENSSL_VERSION));
    }
    if (date)
        printf("%s\n", OpenSSL_version(OPENSSL_BUILT_ON));
    if (platform)
        printf("%s\n", OpenSSL_version(OPENSSL_PLATFORM));
    if (options) {
        printf("options:  ");
        printf("%s ", BN_options());
#ifndef OPENSSL_NO_MD2
        printf("%s ", MD2_options());
#endif
#ifndef OPENSSL_NO_RC4
        printf("%s ", RC4_options());
#endif
#ifndef OPENSSL_NO_DES
        printf("%s ", DES_options());
#endif
#ifndef OPENSSL_NO_IDEA
        printf("%s ", IDEA_options());
#endif
#ifndef OPENSSL_NO_BF
        printf("%s ", BF_options());
#endif
        printf("\n");
    }
    if (cflags)
        printf("%s\n", OpenSSL_version(OPENSSL_CFLAGS));
    if (dir)
        printf("%s\n", OpenSSL_version(OPENSSL_DIR));
    if (engdir)
        printf("%s\n", OpenSSL_version(OPENSSL_ENGINES_DIR));
    if (seed) {
        printf("Seeding source:");
#ifdef OPENSSL_RAND_SEED_RTDSC
        printf(" rtdsc");
#endif
#ifdef OPENSSL_RAND_SEED_RDCPU
        printf(" rdrand ( rdseed rdrand )");
#endif
#ifdef OPENSSL_RAND_SEED_LIBRANDOM
        printf(" C-library-random");
#endif
#ifdef OPENSSL_RAND_SEED_GETRANDOM
        printf(" getrandom-syscall");
#endif
#ifdef OPENSSL_RAND_SEED_DEVRANDOM
        {
            static const char *dev[] = { DEVRANDOM, NULL };
            printlist(" random-device", dev);
        }
#endif
#ifdef OPENSSL_RAND_SEED_EGD
        {
            static const char *dev[] = { DEVRANDOM_EGD, NULL };
            printlist(" EGD", dev);
        }
#endif
#ifdef OPENSSL_RAND_SEED_NONE
        printf(" none");
#endif
#ifdef OPENSSL_RAND_SEED_OS
        printf(" os-specific");
#endif
        printf("\n");
    }
    ret = 0;
 end:
    return ret;
}