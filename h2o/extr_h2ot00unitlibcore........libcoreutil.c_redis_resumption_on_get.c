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
struct TYPE_8__ {int /*<<< orphan*/  sock; } ;
struct st_h2o_redis_resumption_accept_data_t {TYPE_1__ super; int /*<<< orphan*/ * get_command; } ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ redisReply ;
struct TYPE_10__ {int /*<<< orphan*/ * base; } ;
typedef  TYPE_3__ h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ REDIS_REPLY_STRING ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_3__ h2o_decode_base64url (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_ssl_resume_server_handshake (int /*<<< orphan*/ ,TYPE_3__) ; 

__attribute__((used)) static void redis_resumption_on_get(redisReply *reply, void *_accept_data, const char *errstr)
{
    struct st_h2o_redis_resumption_accept_data_t *accept_data = _accept_data;
    accept_data->get_command = NULL;

    h2o_iovec_t session_data;
    if (reply != NULL && reply->type == REDIS_REPLY_STRING) {
        session_data = h2o_decode_base64url(NULL, reply->str, reply->len);
    } else {
        session_data = h2o_iovec_init(NULL, 0);
    }

    h2o_socket_ssl_resume_server_handshake(accept_data->super.sock, session_data);

    if (session_data.base != NULL)
        free(session_data.base);
}