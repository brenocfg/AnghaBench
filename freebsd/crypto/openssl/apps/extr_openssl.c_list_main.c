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
typedef  int HELPLIST_CHOICE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  EVP_CIPHER_do_all_sorted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_do_all_sorted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_cipher ; 
 int /*<<< orphan*/  FT_general ; 
 int /*<<< orphan*/  FT_md ; 
#define  OPT_CIPHER_ALGORITHMS 141 
#define  OPT_CIPHER_COMMANDS 140 
#define  OPT_COMMANDS 139 
#define  OPT_DIGEST_ALGORITHMS 138 
#define  OPT_DIGEST_COMMANDS 137 
#define  OPT_DISABLED 136 
#define  OPT_EOF 135 
#define  OPT_ERR 134 
#define  OPT_HELP 133 
#define  OPT_MISSING_HELP 132 
#define  OPT_ONE 131 
#define  OPT_OPTIONS 130 
#define  OPT_PK_ALGORITHMS 129 
#define  OPT_PK_METHOD 128 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  list_cipher_fn ; 
 int /*<<< orphan*/  list_disabled () ; 
 int /*<<< orphan*/  list_md_fn ; 
 int /*<<< orphan*/  list_missing_help () ; 
 int /*<<< orphan*/  list_options ; 
 int /*<<< orphan*/  list_options_for_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_pkey () ; 
 int /*<<< orphan*/  list_pkey_meth () ; 
 int /*<<< orphan*/  list_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opt_arg () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 char* opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int opt_next () ; 
 scalar_t__ opt_num_rest () ; 

int list_main(int argc, char **argv)
{
    char *prog;
    HELPLIST_CHOICE o;
    int one = 0, done = 0;

    prog = opt_init(argc, argv, list_options);
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_EOF:  /* Never hit, but suppresses warning */
        case OPT_ERR:
opthelp:
            BIO_printf(bio_err, "%s: Use -help for summary.\n", prog);
            return 1;
        case OPT_HELP:
            opt_help(list_options);
            break;
        case OPT_ONE:
            one = 1;
            break;
        case OPT_COMMANDS:
            list_type(FT_general, one);
            break;
        case OPT_DIGEST_COMMANDS:
            list_type(FT_md, one);
            break;
        case OPT_DIGEST_ALGORITHMS:
            EVP_MD_do_all_sorted(list_md_fn, bio_out);
            break;
        case OPT_CIPHER_COMMANDS:
            list_type(FT_cipher, one);
            break;
        case OPT_CIPHER_ALGORITHMS:
            EVP_CIPHER_do_all_sorted(list_cipher_fn, bio_out);
            break;
        case OPT_PK_ALGORITHMS:
            list_pkey();
            break;
        case OPT_PK_METHOD:
            list_pkey_meth();
            break;
        case OPT_DISABLED:
            list_disabled();
            break;
        case OPT_MISSING_HELP:
            list_missing_help();
            break;
        case OPT_OPTIONS:
            list_options_for_command(opt_arg());
            break;
        }
        done = 1;
    }
    if (opt_num_rest() != 0) {
        BIO_printf(bio_err, "Extra arguments given.\n");
        goto opthelp;
    }

    if (!done)
        goto opthelp;

    return 0;
}