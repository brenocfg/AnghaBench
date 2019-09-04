#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* scalar; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 scalar_t__ YOML_TYPE_SCALAR ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_2__*,char*,char const*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

ssize_t h2o_configurator_get_one_of(h2o_configurator_command_t *cmd, yoml_t *node, const char *candidates)
{
    const char *config_str, *cand_str;
    ssize_t config_str_len, cand_index;

    if (node->type != YOML_TYPE_SCALAR)
        goto Error;

    config_str = node->data.scalar;
    config_str_len = strlen(config_str);

    cand_str = candidates;
    for (cand_index = 0;; ++cand_index) {
        if (strncasecmp(cand_str, config_str, config_str_len) == 0 &&
            (cand_str[config_str_len] == '\0' || cand_str[config_str_len] == ',')) {
            /* found */
            return cand_index;
        }
        cand_str = strchr(cand_str, ',');
        if (cand_str == NULL)
            goto Error;
        cand_str += 1; /* skip ',' */
    }
    /* not reached */

Error:
    h2o_configurator_errprintf(cmd, node, "argument must be one of: %s", candidates);
    return -1;
}