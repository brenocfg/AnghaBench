#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ctrl; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int ENGINE_CTRL_GET_CMD_FROM_NAME ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_CTRL_CMD ; 
 int /*<<< orphan*/  ENGINE_R_INVALID_CMD_NAME ; 
 scalar_t__ ENGINE_ctrl (TYPE_1__*,int,long,void*,void (*) ()) ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  ERR_clear_error () ; 

int ENGINE_ctrl_cmd(ENGINE *e, const char *cmd_name,
                    long i, void *p, void (*f) (void), int cmd_optional)
{
    int num;

    if (e == NULL || cmd_name == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    if (e->ctrl == NULL
        || (num = ENGINE_ctrl(e, ENGINE_CTRL_GET_CMD_FROM_NAME,
                              0, (void *)cmd_name, NULL)) <= 0) {
        /*
         * If the command didn't *have* to be supported, we fake success.
         * This allows certain settings to be specified for multiple ENGINEs
         * and only require a change of ENGINE id (without having to
         * selectively apply settings). Eg. changing from a hardware device
         * back to the regular software ENGINE without editing the config
         * file, etc.
         */
        if (cmd_optional) {
            ERR_clear_error();
            return 1;
        }
        ENGINEerr(ENGINE_F_ENGINE_CTRL_CMD, ENGINE_R_INVALID_CMD_NAME);
        return 0;
    }
    /*
     * Force the result of the control command to 0 or 1, for the reasons
     * mentioned before.
     */
    if (ENGINE_ctrl(e, num, i, p, f) > 0)
        return 1;
    return 0;
}