#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* scalar; } ;
struct TYPE_11__ {TYPE_2__ data; } ;
typedef  TYPE_3__ yoml_t ;
struct fastcgi_configurator_t {TYPE_1__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_12__ {scalar_t__ configurator; } ;
typedef  TYPE_4__ h2o_configurator_command_t ;
struct TYPE_9__ {void* document_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_configurator_errprintf (TYPE_4__*,TYPE_3__*,char*) ; 
 void* h2o_iovec_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int on_config_document_root(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct fastcgi_configurator_t *self = (void *)cmd->configurator;

    if (node->data.scalar[0] == '\0') {
        /* unset */
        self->vars->document_root = h2o_iovec_init(NULL, 0);
    } else if (node->data.scalar[0] == '/') {
        /* set */
        self->vars->document_root = h2o_iovec_init(node->data.scalar, strlen(node->data.scalar));
    } else {
        h2o_configurator_errprintf(cmd, node, "value does not start from `/`");
        return -1;
    }
    return 0;
}