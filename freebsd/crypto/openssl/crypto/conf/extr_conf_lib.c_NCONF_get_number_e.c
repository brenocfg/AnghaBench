#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* meth; } ;
struct TYPE_8__ {int (* is_number ) (TYPE_2__ const*,char) ;int (* to_int ) (TYPE_2__ const*,char) ;} ;
typedef  TYPE_2__ CONF ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_F_NCONF_GET_NUMBER_E ; 
 int /*<<< orphan*/  CONF_R_NUMBER_TOO_LARGE ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int const LONG_MAX ; 
 char* NCONF_get_string (TYPE_2__ const*,char const*,char const*) ; 
 int default_is_number (TYPE_2__ const*,char) ; 
 int default_to_int (TYPE_2__ const*,char) ; 

int NCONF_get_number_e(const CONF *conf, const char *group, const char *name,
                       long *result)
{
    char *str;
    long res;
    int (*is_number)(const CONF *, char) = &default_is_number;
    int (*to_int)(const CONF *, char) = &default_to_int;

    if (result == NULL) {
        CONFerr(CONF_F_NCONF_GET_NUMBER_E, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    str = NCONF_get_string(conf, group, name);

    if (str == NULL)
        return 0;

    if (conf != NULL) {
        if (conf->meth->is_number != NULL)
            is_number = conf->meth->is_number;
        if (conf->meth->to_int != NULL)
            to_int = conf->meth->to_int;
    }
    for (res = 0; is_number(conf, *str); str++) {
        const int d = to_int(conf, *str);

        if (res > (LONG_MAX - d) / 10L) {
            CONFerr(CONF_F_NCONF_GET_NUMBER_E, CONF_R_NUMBER_TOO_LARGE);
            return 0;
        }
        res = res * 10 + d;
    }

    *result = res;
    return 1;
}