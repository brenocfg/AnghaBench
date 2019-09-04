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
typedef  scalar_t__ yrmcds_error ;
struct TYPE_3__ {int sock; char* recvbuf; int capacity; scalar_t__ rserial; scalar_t__ text_mode; scalar_t__ invalid; int /*<<< orphan*/ * decompressed; scalar_t__ last_size; scalar_t__ used; int /*<<< orphan*/  lock; scalar_t__ compress_size; scalar_t__ serial; } ;
typedef  TYPE_1__ yrmcds ;
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

yrmcds_error yrmcds_connect(yrmcds* c, const char* node, uint16_t port) {
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
    c->compress_size = 0;
    c->recvbuf = (char*)malloc(1 << 20);
    if( c->recvbuf == NULL ) {
        close(server_fd);
#ifndef LIBYRMCDS_NO_INTERNAL_LOCK
        pthread_mutex_destroy(&(c->lock));
#endif
        return YRMCDS_OUT_OF_MEMORY;
    }
    c->capacity = 1 << 20;
    c->used = 0;
    c->last_size = 0;
    c->decompressed = NULL;
    c->invalid = 0;
    c->text_mode = 0;
    c->rserial = 0;
    return YRMCDS_OK;
}