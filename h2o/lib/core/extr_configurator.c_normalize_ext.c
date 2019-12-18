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
struct TYPE_5__ {char const* scalar; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 scalar_t__ assert_is_extension (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static const char *normalize_ext(h2o_configurator_command_t *cmd, yoml_t *node)
{
    if (strcmp(node->data.scalar, "default") == 0) {
        /* empty string means default */
        return "";
    } else if (assert_is_extension(cmd, node) == 0) {
        return node->data.scalar + 1;
    } else {
        return NULL;
    }
}