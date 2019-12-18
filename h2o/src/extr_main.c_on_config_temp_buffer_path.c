#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* scalar; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  fn_template; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 TYPE_4__ h2o_socket_buffer_mmap_settings ; 
 int snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int on_config_temp_buffer_path(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    char buf[sizeof(h2o_socket_buffer_mmap_settings.fn_template)];

    int len = snprintf(buf, sizeof(buf), "%s%s", node->data.scalar, strrchr(h2o_socket_buffer_mmap_settings.fn_template, '/'));
    if (len >= sizeof(buf)) {
        h2o_configurator_errprintf(cmd, node, "path is too long");
        return -1;
    }
    strcpy(h2o_socket_buffer_mmap_settings.fn_template, buf);

    return 0;
}