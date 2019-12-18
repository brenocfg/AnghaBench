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
struct TYPE_3__ {int /*<<< orphan*/  log_access; int /*<<< orphan*/  dispose; } ;
struct st_h2o_access_logger_t {TYPE_1__ super; int /*<<< orphan*/ * fh; } ;
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
typedef  TYPE_1__ h2o_logger_t ;
typedef  int /*<<< orphan*/  h2o_access_log_filehandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  dispose ; 
 scalar_t__ h2o_create_logger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_mem_addref_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_access ; 

h2o_logger_t *h2o_access_log_register(h2o_pathconf_t *pathconf, h2o_access_log_filehandle_t *fh)
{
    struct st_h2o_access_logger_t *self = (void *)h2o_create_logger(pathconf, sizeof(*self));

    self->super.dispose = dispose;
    self->super.log_access = log_access;
    self->fh = fh;
    h2o_mem_addref_shared(fh);

    return &self->super;
}