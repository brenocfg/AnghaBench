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
typedef  int /*<<< orphan*/  CONF ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_R_NO_SUCH_FILE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  CONF_F_DEF_LOAD ; 
 int /*<<< orphan*/  CONF_R_NO_SUCH_FILE ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_GET_REASON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  ERR_peek_last_error () ; 
 int def_load_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*) ; 

__attribute__((used)) static int def_load(CONF *conf, const char *name, long *line)
{
    int ret;
    BIO *in = NULL;

#ifdef OPENSSL_SYS_VMS
    in = BIO_new_file(name, "r");
#else
    in = BIO_new_file(name, "rb");
#endif
    if (in == NULL) {
        if (ERR_GET_REASON(ERR_peek_last_error()) == BIO_R_NO_SUCH_FILE)
            CONFerr(CONF_F_DEF_LOAD, CONF_R_NO_SUCH_FILE);
        else
            CONFerr(CONF_F_DEF_LOAD, ERR_R_SYS_LIB);
        return 0;
    }

    ret = def_load_bio(conf, in, line);
    BIO_free(in);

    return ret;
}