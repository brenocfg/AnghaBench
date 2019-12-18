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
typedef  int /*<<< orphan*/  TS_RESP_CTX ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  ENV_VALUE_NO ; 
 int /*<<< orphan*/  ENV_VALUE_YES ; 
 char* NCONF_get_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  TS_RESP_CTX_add_flags (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_CONF_invalid (char const*,char const*) ; 

__attribute__((used)) static int ts_CONF_add_flag(CONF *conf, const char *section,
                            const char *field, int flag, TS_RESP_CTX *ctx)
{
    const char *value = NCONF_get_string(conf, section, field);

    if (value) {
        if (strcmp(value, ENV_VALUE_YES) == 0)
            TS_RESP_CTX_add_flags(ctx, flag);
        else if (strcmp(value, ENV_VALUE_NO) != 0) {
            ts_CONF_invalid(section, field);
            return 0;
        }
    }

    return 1;
}