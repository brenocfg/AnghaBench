#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum range { ____Placeholder_range } range ;
struct TYPE_5__ {int build_chain; int /*<<< orphan*/  keyform; int /*<<< orphan*/  certform; int /*<<< orphan*/ * chainfile; int /*<<< orphan*/ * keyfile; int /*<<< orphan*/ * certfile; } ;
typedef  TYPE_1__ SSL_EXCERT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_FMT_PEMDER ; 
#define  OPT_X_CERT 135 
#define  OPT_X_CERTFORM 134 
#define  OPT_X_CHAIN 133 
#define  OPT_X_CHAIN_BUILD 132 
#define  OPT_X_KEY 131 
#define  OPT_X_KEYFORM 130 
#define  OPT_X__FIRST 129 
#define  OPT_X__LAST 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bio_err ; 
 void* opt_arg () ; 
 int /*<<< orphan*/  opt_format (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opt_getprog () ; 
 int /*<<< orphan*/  ssl_excert_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ssl_excert_prepend (TYPE_1__**) ; 

int args_excert(int opt, SSL_EXCERT **pexc)
{
    SSL_EXCERT *exc = *pexc;

    assert(opt > OPT_X__FIRST);
    assert(opt < OPT_X__LAST);

    if (exc == NULL) {
        if (!ssl_excert_prepend(&exc)) {
            BIO_printf(bio_err, " %s: Error initialising xcert\n",
                       opt_getprog());
            goto err;
        }
        *pexc = exc;
    }

    switch ((enum range)opt) {
    case OPT_X__FIRST:
    case OPT_X__LAST:
        return 0;
    case OPT_X_CERT:
        if (exc->certfile != NULL && !ssl_excert_prepend(&exc)) {
            BIO_printf(bio_err, "%s: Error adding xcert\n", opt_getprog());
            goto err;
        }
        *pexc = exc;
        exc->certfile = opt_arg();
        break;
    case OPT_X_KEY:
        if (exc->keyfile != NULL) {
            BIO_printf(bio_err, "%s: Key already specified\n", opt_getprog());
            goto err;
        }
        exc->keyfile = opt_arg();
        break;
    case OPT_X_CHAIN:
        if (exc->chainfile != NULL) {
            BIO_printf(bio_err, "%s: Chain already specified\n",
                       opt_getprog());
            goto err;
        }
        exc->chainfile = opt_arg();
        break;
    case OPT_X_CHAIN_BUILD:
        exc->build_chain = 1;
        break;
    case OPT_X_CERTFORM:
        if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &exc->certform))
            return 0;
        break;
    case OPT_X_KEYFORM:
        if (!opt_format(opt_arg(), OPT_FMT_PEMDER, &exc->keyform))
            return 0;
        break;
    }
    return 1;

 err:
    ERR_print_errors(bio_err);
    ssl_excert_free(exc);
    *pexc = NULL;
    return 0;
}