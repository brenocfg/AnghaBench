#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ yrmcds_error ;
struct TYPE_4__ {int /*<<< orphan*/ * records; scalar_t__ capacity; scalar_t__ count; } ;
struct TYPE_5__ {int sock; char* recvbuf; int capacity; TYPE_1__ stats; scalar_t__ invalid; scalar_t__ last_size; scalar_t__ used; int /*<<< orphan*/  lock; scalar_t__ serial; } ;
typedef  TYPE_2__ yrmcds_cnt ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ YRMCDS_BAD_ARGUMENT ; 
 scalar_t__ YRMCDS_OK ; 
 scalar_t__ YRMCDS_OUT_OF_MEMORY ; 
 scalar_t__ YRMCDS_SYSTEM_ERROR ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect_to_server (char const*,int /*<<< orphan*/ ,int*) ; 
 int errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

yrmcds_error yrmcds_cnt_connect(yrmcds_cnt* c, const char* node, uint16_t port) {
    if( c == NULL )
        return YRMCDS_BAD_ARGUMENT;
#ifndef LIBYRMCDS_NO_INTERNAL_LOCK
    int e = pthread_mutex_init(&(c->lock), NULL);
    if( e != 0 ) {
        errno = e;
        return YRMCDS_SYSTEM_ERROR;
    }
#endif // ! LIBYRMCDS_NO_INTERNAL_LOCK
    int server_fd;
    yrmcds_error err = connect_to_server(node, port, &server_fd);
    if( err != YRMCDS_OK )
        return err;
    c->sock = server_fd;
    c->serial = 0;
    c->recvbuf = (char*)malloc(4096);
    if( c->recvbuf == NULL ) {
        close(server_fd);
#ifndef LIBYRMCDS_NO_INTERNAL_LOCK
        pthread_mutex_destroy(&(c->lock));
#endif
        return YRMCDS_OUT_OF_MEMORY;
    }
    c->capacity = 4096;
    c->used = 0;
    c->last_size = 0;
    c->invalid = 0;
    c->stats.count = c->stats.capacity = 0;
    c->stats.records = NULL;
    return YRMCDS_OK;
}