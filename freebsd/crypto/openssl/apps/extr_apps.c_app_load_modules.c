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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ CONF_modules_load (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCONF_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * app_load_config_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  default_config_file ; 

int app_load_modules(const CONF *config)
{
    CONF *to_free = NULL;

    if (config == NULL)
        config = to_free = app_load_config_quiet(default_config_file);
    if (config == NULL)
        return 1;

    if (CONF_modules_load(config, NULL, 0) <= 0) {
        BIO_printf(bio_err, "Error configuring OpenSSL modules\n");
        ERR_print_errors(bio_err);
        NCONF_free(to_free);
        return 0;
    }
    NCONF_free(to_free);
    return 1;
}