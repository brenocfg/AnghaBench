#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ctx; TYPE_3__** buf; } ;
typedef  TYPE_1__ h2o_httpclient_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 scalar_t__ cnt_left ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_3__**,int /*<<< orphan*/ ) ; 
 char const* h2o_httpclient_error_is_eos ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pool ; 
 int /*<<< orphan*/  start_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int on_body(h2o_httpclient_t *client, const char *errstr)
{
    if (errstr != NULL && errstr != h2o_httpclient_error_is_eos) {
        on_error(client->ctx, errstr);
        return -1;
    }

    fwrite((*client->buf)->bytes, 1, (*client->buf)->size, stdout);
    fflush(stdout);
    h2o_buffer_consume(&(*client->buf), (*client->buf)->size);

    if (errstr == h2o_httpclient_error_is_eos) {
        if (--cnt_left != 0) {
            /* next attempt */
            h2o_mem_clear_pool(&pool);
            ftruncate(fileno(stdout), 0); /* ignore error when stdout is a tty */
            start_request(client->ctx);
        }
    }

    return 0;
}