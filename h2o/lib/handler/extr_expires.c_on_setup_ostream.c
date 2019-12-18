#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct st_expires_t {TYPE_1__ value; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int status; int /*<<< orphan*/  headers; } ;
struct TYPE_8__ {TYPE_2__ res; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_ostream_t ;
typedef  int /*<<< orphan*/  h2o_filter_t ;

/* Variables and functions */
#define  H2O_EXPIRES_MODE_ABSOLUTE 129 
#define  H2O_EXPIRES_MODE_MAX_AGE 128 
 int /*<<< orphan*/  H2O_TOKEN_CACHE_CONTROL ; 
 int /*<<< orphan*/  H2O_TOKEN_EXPIRES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_set_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_set_header_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_setup_next_ostream (TYPE_3__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void on_setup_ostream(h2o_filter_t *_self, h2o_req_t *req, h2o_ostream_t **slot)
{
    struct st_expires_t *self = (void *)_self;

    switch (req->res.status) {
    case 200:
    case 201:
    case 204:
    case 206:
    case 301:
    case 302:
    case 303:
    case 304:
    case 307:
        switch (self->mode) {
        case H2O_EXPIRES_MODE_ABSOLUTE:
            h2o_set_header(&req->pool, &req->res.headers, H2O_TOKEN_EXPIRES, self->value.base, self->value.len, 0);
            break;
        case H2O_EXPIRES_MODE_MAX_AGE:
            h2o_set_header_token(&req->pool, &req->res.headers, H2O_TOKEN_CACHE_CONTROL, self->value.base, self->value.len);
            break;
        default:
            assert(0);
            break;
        }
        break;
    default:
        break;
    }

    h2o_setup_next_ostream(req, slot);
}