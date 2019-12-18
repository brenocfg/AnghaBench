#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  _refcnt; } ;
typedef  TYPE_1__ yoml_t ;
typedef  int /*<<< orphan*/  resolve_tag_arg_t ;

/* Variables and functions */
 TYPE_1__* resolve_env_tag (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* resolve_file_tag (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static yoml_t *resolve_tag(const char *tag, yoml_t *node, void *cb_arg)
{
    resolve_tag_arg_t *arg = (resolve_tag_arg_t *)cb_arg;

    if (strcmp(tag, "!file") == 0) {
        return resolve_file_tag(node, arg);
    }

    if (strcmp(tag, "!env") == 0) {
        return resolve_env_tag(node, arg);
    }

    /* otherwise, return the node itself */
    ++node->_refcnt;
    return node;
}