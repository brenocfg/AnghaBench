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
struct TYPE_3__ {int err; char const* errstr; } ;
typedef  TYPE_1__ redisAsyncContext ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
#define  REDIS_ERR_EOF 133 
#define  REDIS_ERR_IO 132 
#define  REDIS_ERR_OOM 131 
#define  REDIS_ERR_OTHER 130 
#define  REDIS_ERR_PROTOCOL 129 
#define  REDIS_OK 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  h2o_fatal (char*) ; 
 char const* h2o_redis_error_connect_timeout ; 
 char const* h2o_redis_error_connection ; 
 char const* h2o_redis_error_protocol ; 

__attribute__((used)) static const char *get_error(const redisAsyncContext *redis)
{
    switch (redis->err) {
    case REDIS_OK:
        return NULL;
    case REDIS_ERR_IO:
        /* hiredis internally checks socket error and set errno */
        if (errno == ETIMEDOUT) {
            return h2o_redis_error_connect_timeout;
        } else {
            return h2o_redis_error_connection;
        }
    case REDIS_ERR_EOF:
        return h2o_redis_error_connection;
    case REDIS_ERR_PROTOCOL:
        return h2o_redis_error_protocol;
    case REDIS_ERR_OOM:
    case REDIS_ERR_OTHER:
        return redis->errstr;
    default:
        h2o_fatal("FIXME");
    }
}