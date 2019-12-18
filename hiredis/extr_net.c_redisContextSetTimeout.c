#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tv ;
typedef  int /*<<< orphan*/  timeout_msec ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ redisContext ;
typedef  int DWORD ;

/* Variables and functions */
 int REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_IO ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  __redisSetErrorFromErrno (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ; 

int redisContextSetTimeout(redisContext *c, const struct timeval tv) {
    const void *to_ptr = &tv;
    size_t to_sz = sizeof(tv);
#ifdef _WIN32
    DWORD timeout_msec = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    to_ptr = &timeout_msec;
    to_sz = sizeof(timeout_msec);
#endif
    if (setsockopt(c->fd,SOL_SOCKET,SO_RCVTIMEO,to_ptr,to_sz) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_RCVTIMEO)");
        return REDIS_ERR;
    }
    if (setsockopt(c->fd,SOL_SOCKET,SO_SNDTIMEO,to_ptr,to_sz) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_SNDTIMEO)");
        return REDIS_ERR;
    }
    return REDIS_OK;
}