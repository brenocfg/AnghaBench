#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ h2o_headers_t ;
struct TYPE_9__ {TYPE_3__* name; } ;
typedef  TYPE_2__ h2o_headers_command_t ;
typedef  int /*<<< orphan*/  h2o_header_t ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int h2o_find_header (TYPE_1__*,void*,int) ; 
 int h2o_find_header_by_str (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ h2o_iovec_is_token (TYPE_3__*) ; 

__attribute__((used)) static h2o_header_t *find_header(h2o_headers_t *headers, h2o_headers_command_t *cmd)
{
    ssize_t index;

    if (h2o_iovec_is_token(cmd->name)) {
        index = h2o_find_header(headers, (void *)cmd->name, -1);
    } else {
        index = h2o_find_header_by_str(headers, cmd->name->base, cmd->name->len, -1);
    }
    if (index == -1)
        return NULL;
    return headers->entries + index;
}