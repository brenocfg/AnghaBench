#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ssl; } ;
typedef  TYPE_1__ redisSSLContext ;
struct TYPE_7__ {int flags; TYPE_1__* privdata; } ;
typedef  TYPE_2__ redisContext ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int REDIS_BLOCK ; 
 int /*<<< orphan*/  REDIS_ERR_EOF ; 
 int /*<<< orphan*/  REDIS_ERR_IO ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  __redisSetError (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ errno ; 
 scalar_t__ maybeCheckWant (TYPE_1__*,int) ; 

__attribute__((used)) static int redisSSLRead(redisContext *c, char *buf, size_t bufcap) {
    redisSSLContext *rssl = c->privdata;

    int nread = SSL_read(rssl->ssl, buf, bufcap);
    if (nread > 0) {
        return nread;
    } else if (nread == 0) {
        __redisSetError(c, REDIS_ERR_EOF, "Server closed the connection");
        return -1;
    } else {
        int err = SSL_get_error(rssl->ssl, nread);
        if (c->flags & REDIS_BLOCK) {
            /**
             * In blocking mode, we should never end up in a situation where
             * we get an error without it being an actual error, except
             * in the case of EINTR, which can be spuriously received from
             * debuggers or whatever.
             */
            if (errno == EINTR) {
                return 0;
            } else {
                const char *msg = NULL;
                if (errno == EAGAIN) {
                    msg = "Resource temporarily unavailable";
                }
                __redisSetError(c, REDIS_ERR_IO, msg);
                return -1;
            }
        }

        /**
         * We can very well get an EWOULDBLOCK/EAGAIN, however
         */
        if (maybeCheckWant(rssl, err)) {
            return 0;
        } else {
            __redisSetError(c, REDIS_ERR_IO, NULL);
            return -1;
        }
    }
}