#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  on_req; int /*<<< orphan*/  dispose; int /*<<< orphan*/  on_context_dispose; int /*<<< orphan*/  on_context_init; } ;
struct st_h2o_specific_file_handler_t {int flags; TYPE_1__ super; int /*<<< orphan*/ * mime_type; int /*<<< orphan*/  real_path; } ;
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
typedef  int /*<<< orphan*/  h2o_mimemap_type_t ;
typedef  TYPE_1__ h2o_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 scalar_t__ h2o_create_handler (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_mem_addref_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_strdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  specific_handler_on_context_dispose ; 
 int /*<<< orphan*/  specific_handler_on_context_init ; 
 int /*<<< orphan*/  specific_handler_on_dispose ; 
 int /*<<< orphan*/  specific_handler_on_req ; 

h2o_handler_t *h2o_file_register_file(h2o_pathconf_t *pathconf, const char *real_path, h2o_mimemap_type_t *mime_type, int flags)
{
    struct st_h2o_specific_file_handler_t *self = (void *)h2o_create_handler(pathconf, sizeof(*self));

    self->super.on_context_init = specific_handler_on_context_init;
    self->super.on_context_dispose = specific_handler_on_context_dispose;
    self->super.dispose = specific_handler_on_dispose;
    self->super.on_req = specific_handler_on_req;

    self->real_path = h2o_strdup(NULL, real_path, SIZE_MAX);
    h2o_mem_addref_shared(mime_type);
    self->mime_type = mime_type;
    self->flags = flags;

    return &self->super;
}