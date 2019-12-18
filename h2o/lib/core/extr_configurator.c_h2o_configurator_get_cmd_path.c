#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_ROOT ; 
 char* H2O_TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 char* getenv (char*) ; 
 char* h2o_mem_alloc (scalar_t__) ; 
 TYPE_1__ h2o_strdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 

char *h2o_configurator_get_cmd_path(const char *cmd)
{
    char *root, *cmd_fullpath;

    /* just return the cmd (being strdup'ed) in case we do not need to prefix the value */
    if (cmd[0] == '/' || strchr(cmd, '/') == NULL)
        goto ReturnOrig;

    /* obtain root */
    if ((root = getenv("H2O_ROOT")) == NULL) {
        root = H2O_TO_STR(H2O_ROOT);
    }

    /* build full-path and return */
    cmd_fullpath = h2o_mem_alloc(strlen(root) + strlen(cmd) + 2);
    sprintf(cmd_fullpath, "%s/%s", root, cmd);
    return cmd_fullpath;

ReturnOrig:
    return h2o_strdup(NULL, cmd, SIZE_MAX).base;
}