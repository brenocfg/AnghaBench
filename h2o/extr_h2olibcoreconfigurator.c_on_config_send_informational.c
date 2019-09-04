#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct TYPE_5__ {TYPE_1__* globalconf; } ;
typedef  TYPE_2__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
struct TYPE_4__ {int /*<<< orphan*/  send_informational_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_INFORMATIONAL_MODE_ALL ; 
 int /*<<< orphan*/  H2O_SEND_INFORMATIONAL_MODE_EXCEPT_H1 ; 
 int /*<<< orphan*/  H2O_SEND_INFORMATIONAL_MODE_NONE ; 
 int h2o_configurator_get_one_of (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int on_config_send_informational(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    switch (h2o_configurator_get_one_of(cmd, node, "except-h1,none,all")) {
    case 0:
        ctx->globalconf->send_informational_mode = H2O_SEND_INFORMATIONAL_MODE_EXCEPT_H1;
        break;
    case 1:
        ctx->globalconf->send_informational_mode = H2O_SEND_INFORMATIONAL_MODE_NONE;
        break;
    case 2:
        ctx->globalconf->send_informational_mode = H2O_SEND_INFORMATIONAL_MODE_ALL;
        break;
    default:
        return -1;
    }
    return 0;
}