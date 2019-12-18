#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_loggers; int /*<<< orphan*/  pool; int /*<<< orphan*/ * error_logs; TYPE_2__** loggers; int /*<<< orphan*/ * pathconf; int /*<<< orphan*/  _timeout_entry; } ;
typedef  TYPE_1__ h2o_req_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* log_access ) (TYPE_2__*,TYPE_1__*) ;} ;
typedef  TYPE_2__ h2o_logger_t ;

/* Variables and functions */
 int /*<<< orphan*/  close_generator_and_filters (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*) ; 

void h2o_dispose_request(h2o_req_t *req)
{
    close_generator_and_filters(req);

    h2o_timer_unlink(&req->_timeout_entry);

    if (req->pathconf != NULL) {
        h2o_logger_t **logger = req->loggers, **end = logger + req->num_loggers;
        for (; logger != end; ++logger) {
            (*logger)->log_access((*logger), req);
        }
    }

    if (req->error_logs != NULL)
        h2o_buffer_dispose(&req->error_logs);

    h2o_mem_clear_pool(&req->pool);
}