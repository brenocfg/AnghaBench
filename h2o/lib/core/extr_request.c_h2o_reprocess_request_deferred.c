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
struct st_reprocess_request_deferred_t {int is_delegated; int /*<<< orphan*/ * overrides; void* path; void* authority; int /*<<< orphan*/  const* scheme; void* method; } ;
typedef  int /*<<< orphan*/  h2o_url_scheme_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_req_overrides_t ;
typedef  void* h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ create_deferred_action (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_reprocess_request_cb ; 

void h2o_reprocess_request_deferred(h2o_req_t *req, h2o_iovec_t method, const h2o_url_scheme_t *scheme, h2o_iovec_t authority,
                                    h2o_iovec_t path, h2o_req_overrides_t *overrides, int is_delegated)
{
    struct st_reprocess_request_deferred_t *args =
        (struct st_reprocess_request_deferred_t *)create_deferred_action(req, sizeof(*args), on_reprocess_request_cb);
    args->method = method;
    args->scheme = scheme;
    args->authority = authority;
    args->path = path;
    args->overrides = overrides;
    args->is_delegated = is_delegated;
}