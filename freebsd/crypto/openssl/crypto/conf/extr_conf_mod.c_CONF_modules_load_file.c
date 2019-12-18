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

/* Variables and functions */
 unsigned long CONF_MFLAGS_IGNORE_MISSING_FILE ; 
 unsigned long CONF_MFLAGS_IGNORE_RETURN_CODES ; 
 scalar_t__ CONF_R_NO_SUCH_FILE ; 
 char* CONF_get1_default_config_file () ; 
 int CONF_modules_load (int /*<<< orphan*/ *,char const*,unsigned long) ; 
 scalar_t__ ERR_GET_REASON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_peek_last_error () ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 scalar_t__ NCONF_load (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NCONF_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 

int CONF_modules_load_file(const char *filename, const char *appname,
                           unsigned long flags)
{
    char *file = NULL;
    CONF *conf = NULL;
    int ret = 0;
    conf = NCONF_new(NULL);
    if (conf == NULL)
        goto err;

    if (filename == NULL) {
        file = CONF_get1_default_config_file();
        if (!file)
            goto err;
    } else
        file = (char *)filename;

    if (NCONF_load(conf, file, NULL) <= 0) {
        if ((flags & CONF_MFLAGS_IGNORE_MISSING_FILE) &&
            (ERR_GET_REASON(ERR_peek_last_error()) == CONF_R_NO_SUCH_FILE)) {
            ERR_clear_error();
            ret = 1;
        }
        goto err;
    }

    ret = CONF_modules_load(conf, appname, flags);

 err:
    if (filename == NULL)
        OPENSSL_free(file);
    NCONF_free(conf);

    if (flags & CONF_MFLAGS_IGNORE_RETURN_CODES)
        return 1;

    return ret;
}