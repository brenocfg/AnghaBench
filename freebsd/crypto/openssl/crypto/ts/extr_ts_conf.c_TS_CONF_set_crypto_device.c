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
 int /*<<< orphan*/  ENV_CRYPTO_DEVICE ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_CONF_set_default_engine (char const*) ; 
 int /*<<< orphan*/  ts_CONF_invalid (char const*,int /*<<< orphan*/ ) ; 

int TS_CONF_set_crypto_device(CONF *conf, const char *section,
                              const char *device)
{
    int ret = 0;

    if (device == NULL)
        device = NCONF_get_string(conf, section, ENV_CRYPTO_DEVICE);

    if (device && !TS_CONF_set_default_engine(device)) {
        ts_CONF_invalid(section, ENV_CRYPTO_DEVICE);
        goto err;
    }
    ret = 1;
 err:
    return ret;
}