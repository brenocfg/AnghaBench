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
struct st_server_timing_filter_t {scalar_t__ enforce; } ;
struct TYPE_5__ {int /*<<< orphan*/  content_length; } ;
struct TYPE_6__ {int send_server_timing; int version; TYPE_1__ res; } ;
typedef  TYPE_2__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_ostream_t ;
typedef  int /*<<< orphan*/  h2o_filter_t ;

/* Variables and functions */
 int H2O_SEND_SERVER_TIMING_BASIC ; 
 int H2O_SEND_SERVER_TIMING_PROXY ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  h2o_setup_next_ostream (TYPE_2__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void on_setup_ostream(h2o_filter_t *_self, h2o_req_t *req, h2o_ostream_t **slot)
{
    struct st_server_timing_filter_t *self = (struct st_server_timing_filter_t *)_self;

    /* indicate the protocol handler to emit server timing header (basic and proxy properties) */
    req->send_server_timing = H2O_SEND_SERVER_TIMING_BASIC | H2O_SEND_SERVER_TIMING_PROXY;

    /* force chunked encoding for HTTP/1.1 if enforce flag is set */
    if (0x101 <= req->version && req->version < 0x200 && self->enforce)
        req->res.content_length = SIZE_MAX;

    h2o_setup_next_ostream(req, slot);
}