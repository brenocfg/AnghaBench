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
typedef  int /*<<< orphan*/  yrmcds_error ;
struct TYPE_3__ {int capacity; scalar_t__ used; char* recvbuf; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ yrmcds ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ RECV_SIZE ; 
 int /*<<< orphan*/  YRMCDS_DISCONNECTED ; 
 int /*<<< orphan*/  YRMCDS_OK ; 
 int /*<<< orphan*/  YRMCDS_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  YRMCDS_SYSTEM_ERROR ; 
 scalar_t__ errno ; 
 scalar_t__ realloc (char*,size_t) ; 
 int recv (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline yrmcds_error recv_data(yrmcds* c) {
    if( (c->capacity - c->used) < RECV_SIZE ) {
        size_t new_capacity = c->capacity * 2;
        char* new_buffer = (char*)realloc(c->recvbuf, new_capacity);
        if( new_buffer == NULL )
            return YRMCDS_OUT_OF_MEMORY;
        c->recvbuf = new_buffer;
        c->capacity = new_capacity;
    }

    ssize_t n;
  AGAIN:
    n = recv(c->sock, c->recvbuf + c->used, RECV_SIZE, 0);
    if( n == -1 ) {
        if( errno == EINTR ) goto AGAIN;
        return YRMCDS_SYSTEM_ERROR;
    }
    if( n == 0 )
        return YRMCDS_DISCONNECTED;
    c->used += (size_t)n;
    return YRMCDS_OK;
}