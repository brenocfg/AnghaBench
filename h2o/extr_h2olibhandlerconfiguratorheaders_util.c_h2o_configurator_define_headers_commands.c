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
struct headers_util_configurator_t {int /*<<< orphan*/  super; int /*<<< orphan*/  get_commands; int /*<<< orphan*/ * child; } ;
typedef  int /*<<< orphan*/  h2o_globalconf_t ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
typedef  int /*<<< orphan*/  h2o_configurator_get_headers_commands_cb ;

/* Variables and functions */
 int H2O_CONFIGURATOR_FLAG_ALL_LEVELS ; 
 int H2O_CONFIGURATOR_FLAG_EXPECT_MAPPING ; 
 int H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR ; 
 scalar_t__ h2o_configurator_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_configurator_define_command (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 char* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  on_config_header_add ; 
 int /*<<< orphan*/  on_config_header_append ; 
 int /*<<< orphan*/  on_config_header_merge ; 
 int /*<<< orphan*/  on_config_header_set ; 
 int /*<<< orphan*/  on_config_header_setifempty ; 
 int /*<<< orphan*/  on_config_header_unset ; 
 size_t strlen (char const*) ; 

void h2o_configurator_define_headers_commands(h2o_globalconf_t *global_conf, h2o_configurator_t *conf, const char *prefix,
                                              h2o_configurator_get_headers_commands_cb get_commands)
{
    struct headers_util_configurator_t *c = (void *)h2o_configurator_create(global_conf, sizeof(*c));
    c->child = conf;
    c->get_commands = get_commands;
    size_t prefix_len = strlen(prefix);

#define DEFINE_CMD_NAME(name, suffix)                                                                                              \
    char *name = h2o_mem_alloc(prefix_len + sizeof(suffix));                                                                       \
    memcpy(name, prefix, prefix_len);                                                                                              \
    memcpy(name + prefix_len, suffix, sizeof(suffix))

    DEFINE_CMD_NAME(add_directive, ".add");
    DEFINE_CMD_NAME(append_directive, ".append");
    DEFINE_CMD_NAME(merge_directive, ".merge");
    DEFINE_CMD_NAME(set_directive, ".set");
    DEFINE_CMD_NAME(setifempty_directive, ".setifempty");
    DEFINE_CMD_NAME(unset_directive, ".unset");
#undef DEFINE_CMD_NAME

#define DEFINE_CMD(name, cb)                                                                                                       \
    h2o_configurator_define_command(                                                                                               \
        &c->super, name,                                                                                                           \
        H2O_CONFIGURATOR_FLAG_ALL_LEVELS | H2O_CONFIGURATOR_FLAG_EXPECT_SCALAR | H2O_CONFIGURATOR_FLAG_EXPECT_MAPPING, cb)
    DEFINE_CMD(add_directive, on_config_header_add);
    DEFINE_CMD(append_directive, on_config_header_append);
    DEFINE_CMD(merge_directive, on_config_header_merge);
    DEFINE_CMD(set_directive, on_config_header_set);
    DEFINE_CMD(setifempty_directive, on_config_header_setifempty);
    DEFINE_CMD(unset_directive, on_config_header_unset);
#undef DEFINE_CMD
}