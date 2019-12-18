#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {char* name; char* section; char* value; } ;
typedef  TYPE_1__ CONF_VALUE ;
typedef  TYPE_2__ CONF ;

/* Variables and functions */
 TYPE_1__* lh_CONF_VALUE_retrieve (int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* ossl_safe_getenv (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

char *_CONF_get_string(const CONF *conf, const char *section,
                       const char *name)
{
    CONF_VALUE *v, vv;
    char *p;

    if (name == NULL)
        return NULL;
    if (conf != NULL) {
        if (section != NULL) {
            vv.name = (char *)name;
            vv.section = (char *)section;
            v = lh_CONF_VALUE_retrieve(conf->data, &vv);
            if (v != NULL)
                return v->value;
            if (strcmp(section, "ENV") == 0) {
                p = ossl_safe_getenv(name);
                if (p != NULL)
                    return p;
            }
        }
        vv.section = "default";
        vv.name = (char *)name;
        v = lh_CONF_VALUE_retrieve(conf->data, &vv);
        if (v != NULL)
            return v->value;
        else
            return NULL;
    } else
        return ossl_safe_getenv(name);
}